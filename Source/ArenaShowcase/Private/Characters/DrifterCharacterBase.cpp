// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DrifterCharacterBase.h"

// Sets default values
ADrifterCharacterBase::ADrifterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ADrifterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

