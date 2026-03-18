// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/BehaviorTree/BTTask_AttackPlayer.h"
#include "Characters/DrifterEnemyBase.h"
#include "AIController.h"
#include "Components/Default/HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"


// Constructor

UBTTask_AttackPlayer::UBTTask_AttackPlayer(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = TEXT("Attack Player");
}

// Execute Task
EBTNodeResult::Type UBTTask_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the controlled pawn (enemy character)
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (!ControlledPawn)
	{
		return EBTNodeResult::Failed; // No pawn to control
	}

	// Cast to the specific enemy type
	ADrifterEnemyBase* EnemyCharacter = Cast<ADrifterEnemyBase>(ControlledPawn);
	if (!EnemyCharacter)
	{
		return EBTNodeResult::Failed; // Not the expected enemy type
	}
	
	// Check if target player is dead
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp)
	{
		AActor* TargetActor = Cast<AActor>(BBComp->GetValueAsObject("Player"));
		if (TargetActor)
		{
			UHealthComponent* TargetHealth = TargetActor->FindComponentByClass<UHealthComponent>();
			if (TargetHealth && TargetHealth->IsDead())
			{
				return EBTNodeResult::Failed;
			}
		}
	}

	// Call the attack function on the enemy character
	EnemyCharacter->AttackPlayer();

	return EBTNodeResult::Succeeded; // Task completed successfully
}