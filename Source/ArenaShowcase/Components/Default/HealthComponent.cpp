// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Default/HealthComponent.h"
#include "Engine/Engine.h" // For GEngine debug messages
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
	CurrentHealth = FMath::Max(CurrentHealth - DamageAmount, 0.0f);
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Enemy is Dead"));
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
}; 