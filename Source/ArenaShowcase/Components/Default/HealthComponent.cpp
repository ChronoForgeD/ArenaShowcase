// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Default/HealthComponent.h"
#include "Engine/Engine.h" // For GEngine debug messages
#include "TimerManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/MovementComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
// Initialize health values
	CurrentHealth = MaxHealth;
	
}

// Heal function
void UHealthComponent::Heal_Implementation(float HealAmount)
{
	CurrentHealth += HealAmount;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

// Take damage function
void UHealthComponent::TakeDamage_Implementation(float DamageAmount)
{
	if (bIsDead) return;
	CurrentHealth = FMath::Max(CurrentHealth - DamageAmount, 0.0f);
	PlayHitReaction();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Damage Taken, Health Remaining: %f."), CurrentHealth));
	// Death Handling
	if (CurrentHealth <= 0)
	{
		Death();
	}
	
}
// Reduce max health function
void UHealthComponent::ReduceMaxHealth_Implementation(float ReductionAmount)
{
	MaxHealth -= ReductionAmount;
	if (MaxHealth < 0)
	{
		MaxHealth = 0;
	}
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

// Death function
void UHealthComponent::Death_Implementation()
{
	// This function can be overridden in Blueprints for custom death behavior
		UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *GetOwner()->GetName());
		USkeletalMeshComponent* Mesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
		if (Mesh)
		{
			Mesh->SetSimulatePhysics(true);
			Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
		}
		UCapsuleComponent* Capsule = GetOwner()->FindComponentByClass<UCapsuleComponent>();
		if (Capsule)
		{
			Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		// Stop any movement
		UMovementComponent* Movement = GetOwner()->FindComponentByClass<UMovementComponent>();
		if (Movement)
		{
			Movement->StopMovementImmediately();
		}
		// Set lifespan to destroy the actor after a delay
		GetOwner()->SetLifeSpan(5.0f); // Destroy the actor after 5 seconds
		UE_LOG(LogTemp, Warning, TEXT("Setting bIsDead to TRUE for: %s"), *GetOwner()->GetName());
		bIsDead = true;
		UE_LOG(LogTemp, Warning, TEXT("About to broadcast OnDeath for %s, listeners: %d"), *GetOwner()->GetName(), OnDeath.IsBound() ? 1 : 0);
		OnDeath.Broadcast();
};

// Reset Health Function
void UHealthComponent::ResetHealth()
{
	CurrentHealth = MaxHealth;
	bIsDead = false;
	UE_LOG(LogTemp, Warning, TEXT("ResetHealth called, setting bIsDead to FALSE"));
}

// Hit Flash Function
void UHealthComponent::PlayHitReaction_Implementation()
{
	UMeshComponent* MeshComp = GetOwner()->FindComponentByClass<UMeshComponent>();
	if (MeshComp)
	{
		if (!OriginalMaterial)
		{
			OriginalMaterial = MeshComp->GetMaterial(0);
		}
		if (!FlashMaterial)
		{
			FlashMaterial = UMaterialInstanceDynamic::Create(FlashBaseMaterial, this);
			FlashMaterial->SetVectorParameterValue(FName("FlashColor"), FlashColor);
		}
		MeshComp->SetMaterial(0, FlashMaterial);
		if (FlashMaterial)
		{
			GetWorld()->GetTimerManager().SetTimer(HitReactionFlashTimer, this, &UHealthComponent::ResetFlash, FlashDuration, false);
		}
	}
}

// Reset Hit Flash
void UHealthComponent::ResetFlash_Implementation()
{
	UMeshComponent* MeshComp = GetOwner()->FindComponentByClass<UMeshComponent>();
	if (FlashMaterial)
	{
		if (MeshComp)
		{
			MeshComp->SetMaterial(0, OriginalMaterial);
		}
	}
}
