// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreSystems/EncounterTrigger.h"
#include "Public/Characters/DrifterCharacter.h"

// Sets default values
AEncounterTrigger::AEncounterTrigger()
{
 	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	TriggerBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);  // Overlap Pawns (player/enemies)
	TriggerBox->SetBoxExtent(FVector(500.0f, 500.0f, 200.0f));  // Adjust size in editor

	// Optional: Make it visible in editor only
	TriggerBox->bHiddenInGame = true;
}

// Called when the game starts or when spawned
void AEncounterTrigger::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AEncounterTrigger::OnOverlapBegin);
}

void AEncounterTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
									   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
									   bool bFromSweep, const FHitResult& SweepResult)
{
	// Filter: Only trigger on player (ADrifterCharacter)
	if (OtherActor && OtherActor->IsA(ADrifterCharacter::StaticClass()))
	{
		// Optional: One-shot trigger (disable after first use)
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// Fire the event!
		OnEncounterStarted.Broadcast();

		UE_LOG(LogTemp, Warning, TEXT("Encounter Trigger activated by player!"));
	}
}