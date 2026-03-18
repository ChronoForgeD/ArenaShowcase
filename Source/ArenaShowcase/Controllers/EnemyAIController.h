// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/Default/HealthComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

UCLASS()
class ARENASHOWCASE_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	// Constructor
public:
	AEnemyAIController();
	// On Possess Grab the Health Component Owner and Cache it and bind the Death Delegate to the OnPawnDeath function
	virtual void OnPossess(APawn* InPawn) override;
	
	// Health Component Pointer
	UPROPERTY() UHealthComponent* HealthComp;
	
	// Perception Component Pointer
	UPROPERTY() UAIPerceptionComponent* PerceptionComp;
	
	//Blackboard Component Pointer
	UPROPERTY() UBlackboardComponent* BBComp;
	
	// Run Behavior Tree
	void StartBehaviorTree();
	
	// On Possessed Pawn Death Function
	UFUNCTION()
	void OnPossessedDeath();
	
	// Behavior Tree Asset Reference
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BTAsset;
	
	// Behavior Tree Component Reference
	UPROPERTY(VisibleAnywhere, Category = "AI")	
	class UBehaviorTreeComponent* BTComp;
	
	// AI Sight Perception Config
	
	
	UFUNCTION()
	void OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);
	
};
