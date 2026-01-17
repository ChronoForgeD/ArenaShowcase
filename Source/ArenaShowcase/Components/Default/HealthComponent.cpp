// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Default/HealthComponent.h"

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

	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
	
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
	CurrentHealth -= DamageAmount;
	if (CurrentHealth <= 0.0f)
	{
		CurrentHealth = 0.0f;
		// Handle death logic here (e.g., notify other components, play animations, etc.)
	}
}
void UHealthComponent::ReduceMaxHealth(float ReductionAmount)
{
	MaxHealth -= ReductionAmount;
	if (MaxHealth < 0.0f)
	{
		MaxHealth = 0.0f;
	}
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}
void UHealthComponent::Heal(float HealAmount)
{
	CurrentHealth += HealAmount;
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

