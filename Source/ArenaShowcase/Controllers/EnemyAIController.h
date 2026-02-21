// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/Default/HealthComponent.h"
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
	
	// Health Component Reference
	UPROPERTY() UHealthComponent* HealthComponent;
	
	// Run Behavior Tree
	bool StartBehaviorTree();
	
	// On Possessed Pawn Death Function
	UFUNCTION()
	void OnPossessedDeath();
	
	// Behavior Tree Asset Reference
	UPROPERTY(EditAnywhere, Category = "AI")
	class UBehaviorTree* BTAsset;
    	
	// Success Flag for Starting Behavior Tree
	bool bSuccess;
private:

	
};
