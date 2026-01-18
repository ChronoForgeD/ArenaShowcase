// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DrifterCharacterBase.h"
#include "AbilitySystemComponent.h"

// Sets default values
ADrifterCharacterBase::ADrifterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	// Adding ability system component.
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(ASCReplicationMode);

}

// Called when the game starts or when spawned
void ADrifterCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	// AbilitySystemComponent is created in the constructor. Validate it here.
	check(AbilitySystemComponent);
}

UAbilitySystemComponent* ADrifterCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UHealthComponent* ADrifterCharacterBase::GetHealthComponent() const
{
	return HealthComponent;
}

void ADrifterCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

void ADrifterCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
}

