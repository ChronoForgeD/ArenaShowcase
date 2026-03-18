// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DrifterCharacterBase.h"
#include "Animation/AnimMontage.h"
#include "CoreHeaders/CombatTypes.h"
#include "DrifterCharacter.generated.h"


/**
 * 
 */

UCLASS()
class ARENASHOWCASE_API ADrifterCharacter : public ADrifterCharacterBase
{
	GENERATED_BODY()
	// I am making a third person character for an arena showcase tech demo with data driven design
public:
	ADrifterCharacter();
	
	// Begin Play OnDeath Binding
	virtual void BeginPlay() override;
	
	// OnPlayerDeath Function
	UFUNCTION()
	void OnPlayerDeath();
	
	// RespawnPlayer Function
	UFUNCTION()
	void RespawnPlayer();
	
	// TArray of Combo Struct
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat")
	TArray<FAttackStruct> ComboAttacks;
	
	// Combo Index variable
	int ComboIndex = 0;
	
	// Timer Handle
	FTimerHandle ComboTimerHandle;
	
	// Respawn Timer Handle
	FTimerHandle RespawnTimerHandle;
	
	// Mid-Attack Bool Check
	bool bIsMidAttack = false;
	
	// Is in combo Bool
	bool bIsInCombo = false;
	
	
	// Melee attack sweep function
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void MeleeAttackSweep(FAttackStruct AttackData);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void ComboAttack();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Ability")
	void ResetCombo();
};
