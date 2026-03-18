// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackPlayer.generated.h"


/**
 * 
 */
UCLASS()
class ARENASHOWCASE_API UBTTask_AttackPlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	// Constructor
	UBTTask_AttackPlayer(const FObjectInitializer& ObjectInitializer);
	
	// Override the ExecuteTask function to perform the attack logic
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
