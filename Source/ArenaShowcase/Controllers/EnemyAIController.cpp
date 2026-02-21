// Fill out your copyright notice in the Description page of Project Settings.

// Include the EnemyAIController header and the DrifterEnemyBase header to access the Behavior Tree and Death Delegate
#include "Controllers/EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/DrifterEnemyBase.h"
#include "Components/Default/HealthComponent.h"
#include "BehaviorTree/BTNode.h"
#include "VisualLogger/VisualLogger.h"



// Constructor
AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = false;
}

// On Possess Function
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ADrifterEnemyBase* Enemy = Cast<ADrifterEnemyBase>(InPawn);
	if (Enemy)
	{
		HealthComp = Enemy->FindComponentByClass<UHealthComponent>();
		if (HealthComp){
		HealthComp->OnDeath.AddUObject(this, &AEnemyAIController::OnPossessedDeath);
		StartBehaviorTree();
		}
	}
}

//Start Behavior Tree
void AEnemyAIController::StartBehaviorTree()
{
		if (BTComp == NULL)
		{
			UE_VLOG(this, LogBehaviorTree, Log, TEXT("RunBehaviorTree: spawning BehaviorTreeComponent.."));

			BTComp = NewObject<UBehaviorTreeComponent>(this);
			BTComp->RegisterComponent();
			REDIRECT_OBJECT_TO_VLOG(BTComp, this);
		}
		// Make sure BrainComponent points at the newly created BT component
		BrainComponent = BTComp;

		check(BTComp != NULL);
		// Run Behavior Tree Asset
		if (BTAsset)
		{
			RunBehaviorTree(BTAsset);
		}
}

// On Possessed Pawn Death Function
void AEnemyAIController::OnPossessedDeath()
{	// Stop the Behavior Tree and Unpossess the Pawn
	if (BTComp == NULL)
	{
		UE_VLOG(this, LogBehaviorTree, Log, TEXT("OnPossessedDeath: BehaviorTreeComponent is NULL, cannot stop tree!"));
		UnPossess();
	}
	else
	{
		BTComp->StopTree();
		UnPossess();
	}
	
}