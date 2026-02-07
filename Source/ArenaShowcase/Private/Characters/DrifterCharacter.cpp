// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DrifterCharacter.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"

//Constructor
ADrifterCharacter::ADrifterCharacter()
{
	// Set default properties if needed
}
// Melee attack sweep implementation
void ADrifterCharacter::MeleeAttackSweep_Implementation()
{
	// Define sweep parameters
	FVector Start = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = Start;
	float SphereRadius = 300.0f;

	// Sphere Overlap Actors
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape CollisionShape = FCollisionShape::MakeSphere(SphereRadius);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore self
	bool bHasOverlaps = GetWorld()->OverlapMultiByChannel(
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
		if (!OverlappedActor) continue;

		UE_LOG(LogTemp, Log, TEXT("Melee Attack Hit Actor: %s"), *OverlappedActor->GetName());
	}
}