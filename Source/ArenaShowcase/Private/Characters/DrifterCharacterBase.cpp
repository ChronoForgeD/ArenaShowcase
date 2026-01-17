// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DrifterCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
ADrifterCharacterBase::ADrifterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

}

// Called when the game starts or when spawned
void ADrifterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// AbilitySystemComponent is created in the constructor. Validate it here.
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("AbilitySystemComponent is null on %s"), *GetName());
	}
}

UAbilitySystemComponent* ADrifterCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UHealthComponent* ADrifterCharacterBase::GetHealthComponent() const
{
	return HealthComponent;
}
