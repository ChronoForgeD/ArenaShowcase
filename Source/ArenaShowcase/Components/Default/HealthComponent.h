// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOWCASE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "DamageHandling")
	void TakeDamage(float DamageAmount);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "MaxHealthReductionHandling")
	void ReduceMaxHealth(float ReductionAmount);
	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "HealthHealingHandling")
	void Heal(float HealAmount);
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Health properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float CurrentHealth;
	
};
