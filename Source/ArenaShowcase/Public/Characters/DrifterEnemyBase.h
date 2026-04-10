// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DrifterCharacterBase.h"
#include "CoreHeaders/CombatTypes.h"
#include "DrifterEnemyBase.generated.h"


/**
 * 
 */

UCLASS()
class ARENASHOWCASE_API ADrifterEnemyBase : public ADrifterCharacterBase
{
	GENERATED_BODY()
	public:
	ADrifterEnemyBase();
	
	// Mid-Attack Bool Check
	bool bIsMidAttack = false;
	
	// Attack Struct
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	FAttackStruct EnemyAttackData;
	
	// Attack Function
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Combat")
	void AttackPlayer();
	
	// Enemy Reset for Object Pooling Recycling Function
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ResetEnemy();
	
};
