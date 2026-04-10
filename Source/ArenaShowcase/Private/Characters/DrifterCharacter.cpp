// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DrifterCharacter.h"
#include "CollisionDebugDrawingPublic.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h" 
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimMontage.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Components/Default/HealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Perception/AISense_Sight.h"

//Constructor
ADrifterCharacter::ADrifterCharacter()
{
	// Set default properties if needed
	UAIPerceptionStimuliSourceComponent* StimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>("StimuliSource");
	StimuliSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliSource->RegisterWithPerceptionSystem();
}

// Begin Play Override for OnDeath Binding
void ADrifterCharacter::BeginPlay()
{
	Super::BeginPlay();
	UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health Component Found, Binding Death Delegate"));
		HealthComp->OnDeath.AddDynamic(this, &ADrifterCharacter::OnPlayerDeath);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Health Component NOT Found"));
	}
}

// OnPlayerDeath Function
void ADrifterCharacter::OnPlayerDeath()
{
	// Handle player death logic (e.g., play animation, disable input)
	UE_LOG(LogTemp, Warning, TEXT("Player has died!"));
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controller Found, Disabling Input"));
		PC->DisableInput(PC);
		SetLifeSpan(0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player Controller Cast Failed"));
	}
	SetLifeSpan(0);
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ADrifterCharacter::RespawnPlayer, 3.0f, false);
}

// RespawnPlayer Function
void ADrifterCharacter::RespawnPlayer()
{
	
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->EnableInput(PC);
	}
		// Reset Health
	UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp)
	{
		HealthComp->ResetHealth();
	}
		
		if (GetMesh())
		{
			GetMesh()->SetSimulatePhysics(false);
			GetMesh()->SetCollisionProfileName(TEXT("CharacterMesh"));
			GetMesh()->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		}
		
		if (GetCapsuleComponent())
		{
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	
	// Spawn Player
    		FVector SpawnLocation = FVector(0.0f, 0.0f, 300.0f);
    		SetActorLocation(SpawnLocation); // Move to spawn location
			UE_LOG(LogTemp, Warning, TEXT("RespawnPlayer called"));
}

// Melee attack sweep implementation
void ADrifterCharacter::MeleeAttackSweep_Implementation(FAttackStruct AttackData)
{
	// Define sweep parameters
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start;
	float SphereRadius = AttackData.Radius;
	
	// Sphere Overlap Actors
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore self
	bool bHasOverlaps =  GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		Start,
		FQuat::Identity,
		ECC_Pawn,
		CollisionShape,
		QueryParams
	);
	// Debug drawing
	DrawDebugSphere(GetWorld(), Start, SphereRadius, 12, FColor::Red, false, 2.0f);
	
	for (const FOverlapResult& Result : OverlapResults)
	{
		AActor* OverlappedActor = Result.GetActor();
		if (OverlappedActor)	
		{
			// Cone check
			if (FVector::DotProduct(ForwardVector, (OverlappedActor->GetActorLocation() - Start).GetSafeNormal()) < AttackData.ArcAngle)
			{
				continue; // Not within the cone angle
			}
			UHealthComponent* HealthComp = OverlappedActor->FindComponentByClass<UHealthComponent>();
			if (HealthComp)
			{
				float DamageAmount = AttackData.Damage;  // Hardcode for now
				HealthComp->TakeDamage(DamageAmount);
				UE_LOG(LogTemp, Log, TEXT("Dealt %f damage to: %s"), DamageAmount, *OverlappedActor->GetName());
			}
		}
	}
}
	
	// Combo Attack Implementation
	
	void ADrifterCharacter::ComboAttack_Implementation()
	{
	UE_LOG(LogTemp, Warning, TEXT("ComboAttack called"));
	UHealthComponent* HealthComp = FindComponentByClass<UHealthComponent>();
	if (HealthComp && HealthComp->IsDead())
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is dead, blocking attack"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Player is alive, proceeding with combo"));
		if (bIsMidAttack) return; // busy, ignore input
		
			if (!bIsInCombo)
			{
				if (ComboAttacks.Num() > 0)
				{
				bIsMidAttack = true;
				bIsInCombo = true;
				FAttackStruct FirstAttack = ComboAttacks[0];
					// Check and Play Anim Montage
					if (FirstAttack.Montage)
					{
						PlayAnimMontage(FirstAttack.Montage);
					}
				MeleeAttackSweep(FirstAttack);
				ComboIndex = 1;
				bIsMidAttack = false;
				GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ADrifterCharacter::ResetCombo, 1.0f, false);
				}
			}
		else
		 {
			if (ComboIndex < ComboAttacks.Num())
			{
				bIsMidAttack = true;
				FAttackStruct CurrentAttack = ComboAttacks[ComboIndex];
				// Check and Play Anim Montage
				if (CurrentAttack.Montage)
				{
					PlayAnimMontage(CurrentAttack.Montage);
				}
				MeleeAttackSweep(CurrentAttack);
				ComboIndex++;
				bIsMidAttack = false;
				GetWorld()->GetTimerManager().SetTimer(ComboTimerHandle, this, &ADrifterCharacter::ResetCombo, 1.0f, false);
			}
			
			else
			{
				ResetCombo();
			}
		 }
	}
	
	// Reset Combo Function
	void ADrifterCharacter::ResetCombo_Implementation()
	{
		ComboIndex = 0;
		bIsInCombo = false;
		bIsMidAttack = false;
	}

