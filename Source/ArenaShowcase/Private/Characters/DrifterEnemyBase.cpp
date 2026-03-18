// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DrifterEnemyBase.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Engine/OverlapResult.h"
#include "Components/Default/HealthComponent.h"
#include "CoreHeaders/CombatTypes.h"

// Constructor

ADrifterEnemyBase::ADrifterEnemyBase()
{
	// Set default properties if needed
}

// Attack Player Function Implementation

void ADrifterEnemyBase::AttackPlayer_Implementation()
{
	if (bIsMidAttack) return; // busy, ignore input
	
	{
		// Define sweep parameters
		FVector Start = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		FVector End = Start;
		float SphereRadius = EnemyAttackData.Radius;
	
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
				if (FVector::DotProduct(ForwardVector, (OverlappedActor->GetActorLocation() - Start).GetSafeNormal()) < EnemyAttackData.ArcAngle)
				{
					continue; // Not within the cone angle
				}
				UHealthComponent* HealthComp = OverlappedActor->FindComponentByClass<UHealthComponent>();
				if (HealthComp)
				{	
					float DamageAmount = EnemyAttackData.Damage;  // Use the damage from the attack data
					HealthComp->TakeDamage(DamageAmount);
					UE_LOG(LogTemp, Log, TEXT("Dealt %f damage to: %s"), DamageAmount, *OverlappedActor->GetName());
				}
			}
		}
	}
}
