// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DrifterCharacterBase.generated.h"

UCLASS(Abstract)
class ARENASHOWCASE_API ADrifterCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADrifterCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
