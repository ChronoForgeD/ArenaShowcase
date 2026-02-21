// Fill out your copyright notice in the Description page of Project Settings.

// Include the EnemyAIController header and the DrifterEnemyBase header to access the Behavior Tree and Death Delegate
#include "Controllers/EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/DrifterEnemyBase.h"
#include "Components/Default/HealthComponent.h"
// Include the Visual Logger for debugging purposes
#include "BehaviorTree/BTNode.h"
#include "VisualLogger/VisualLogger.h"



// Constructor
AEnemyAIController::AEnemyAIController()
{	// Set this AI controller to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// On Possess Grab the Health Component Owner and Cache it and bind the Death Delegate to the OnPawnDeath function
void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ADrifterEnemyBase* Enemy = Cast<ADrifterEnemyBase>(InPawn);
	if (Enemy)
	{
		UHealthComponent* HealthComp = Enemy->FindComponentByClass<UHealthComponent>();
		if (HealthComp){
		HealthComp->OnDeath.AddUObject(this, &AEnemyAIController::OnPossessedDeath);
		StartBehaviorTree();
		}
	}
}

//Start Behavior Tree
bool AEnemyAIController::StartBehaviorTree()
{
	if (BTAsset == NULL)
	{
		UE_VLOG(this, LogBehaviorTree, Warning, TEXT("RunBehaviorTree: Unable to run NULL behavior tree"));
		return false;
	}

	bool bSuccess = true;
	
	UBlackboardComponent* BlackboardComp = Blackboard;
	if (BTAsset->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BTAsset->BlackboardAsset) == false))
	{
		bSuccess = UseBlackboard(BTAsset->BlackboardAsset, BlackboardComp);
	}

	if (bSuccess)
	{
		UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
		if (BTComp == NULL)
		{
			UE_VLOG(this, LogBehaviorTree, Log, TEXT("RunBehaviorTree: spawning BehaviorTreeComponent.."));

			BTComp = NewObject<UBehaviorTreeComponent>(this);
			BTComp->RegisterComponent();
			REDIRECT_OBJECT_TO_VLOG(BTComp, this);
		}
		
		// make sure BrainComponent points at the newly created BT component
		BrainComponent = BTComp;

		check(BTComp != NULL);
		BTComp->StartTree(*BTAsset, EBTExecutionMode::Looped);
	}

	return bSuccess;
}

// On Possessed Pawn Death Function
void AEnemyAIController::OnPossessedDeath()
{	// Stop the Behavior Tree and Unpossess the Pawn
	StopTree();
	UnPossess();
}