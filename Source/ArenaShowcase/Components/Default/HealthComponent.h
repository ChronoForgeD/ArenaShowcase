// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOWCASE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	// Delegate for death event
	UPROPERTY(BlueprintAssignable)
	FOnDeath OnDeath;
	
	// Public Getter for bIsDead
	bool IsDead() const { return bIsDead; }
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DamageHandling")
	void TakeDamage(float DamageAmount);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MaxHealthReductionHandling")
	void ReduceMaxHealth(float ReductionAmount);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HealthHealingHandling")
	void Heal(float HealAmount);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "DeathHandling")
	void Death();
	
	UFUNCTION()
	void ResetHealth();
	
	// Hit Reaction Properties
	FTimerHandle HitReactionFlashTimer;
	
	UPROPERTY(BlueprintReadWrite, Category = "HitReaction")
	UMaterialInterface* OriginalMaterial;
	
	UPROPERTY(BlueprintReadWrite, Category = "HitReaction")
	UMaterialInstanceDynamic* FlashMaterial;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HitReaction")
	void PlayHitReaction();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "HitReaction")
	void ResetFlash();
	
	UPROPERTY(EditAnywhere, Category = "HitReaction")
	float FlashDuration = 0.5;
	
	UPROPERTY(EditAnywhere, Category = "HitReaction")
	FLinearColor FlashColor = FLinearColor::Red;
	
	UPROPERTY(EditAnywhere, Category = "HitReaction")
	UMaterialInterface* FlashBaseMaterial;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	// Health properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float CurrentHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	bool bIsDead;
};
