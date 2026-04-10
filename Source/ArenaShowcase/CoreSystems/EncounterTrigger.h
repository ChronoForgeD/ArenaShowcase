// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "EncounterTrigger.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEncounterStartedSignature);  // Expose this to BP if needed

UCLASS()
class ARENASHOWCASE_API AEncounterTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEncounterTrigger();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* TriggerBox;

	// Delegate for when fight starts (Encounter Manager will bind to this)
	UPROPERTY(BlueprintAssignable, Category = "Encounter")
	FOnEncounterStartedSignature OnEncounterStarted;

protected:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
						int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

};
