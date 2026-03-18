// Fill out your copyright notice in the Description page of Project Settings.

// Include the EnemyAIController header and the DrifterEnemyBase header to access the Behavior Tree and Death Delegate
#include "Controllers/EnemyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Characters/DrifterEnemyBase.h"
#include "Components/Default/HealthComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BTNode.h"
#include "VisualLogger/VisualLogger.h"



// Constructor
AEnemyAIController::AEnemyAIController()
{
	PrimaryActorTick.bCanEverTick = false;
	PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	UAISenseConfig_Sight* SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("SightConfig");
	SightConfig->SightRadius = 1500.0f;
	SightConfig->LoseSightRadius = 2000.0f;
	SightConfig->PeripheralVisionAngleDegrees = 90.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	PerceptionComp->ConfigureSense(*SightConfig);
	PerceptionComp->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
	SetPerceptionComponent(*PerceptionComp);
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
			BBComp = GetBlackboardComponent();
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

// On Perception Updated Function
void AEnemyAIController::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (!BBComp) return;
	// Log the Perception Update
	UE_LOG(LogTemp, Warning, TEXT("Perception Updated: %s"), *Actor->GetName());
	// Perception Update Handling
	if (Actor->ActorHasTag("Player") && Stimulus.WasSuccessfullySensed())
	{
		BBComp->SetValueAsObject("Player", Actor);
	}
	else if (Actor->ActorHasTag("Player") && !Stimulus.WasSuccessfullySensed())
	{
		BBComp->ClearValue("Player");
	}
}