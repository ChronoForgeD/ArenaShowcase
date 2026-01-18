// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "DrifterCharacterBase.generated.h"

class UAbilitySystemComponent;

class UHealthComponent;

UCLASS(Abstract)
class ARENASHOWCASE_API ADrifterCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrifterCharacterBase();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "StaticMesh")
	class UStaticMeshComponent* StaticMeshComponent;
	
	// Ability System Component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AbilitySystem")
	class UAbilitySystemComponent* AbilitySystemComponent;
	
	// Health Component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "HealthSystem")
	class UHealthComponent* HealthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual class UAbilitySystemComponent *GetAbilitySystemComponent() const override;
	
	virtual class UHealthComponent* GetHealthComponent() const;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilitySystem")
	EGameplayEffectReplicationMode ASCReplicationMode = EGameplayEffectReplicationMode::Mixed;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;
};
