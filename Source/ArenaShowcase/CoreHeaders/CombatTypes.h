
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimMontage.h"
#include "CombatTypes.generated.h"

/**
* 
 */

// File to house different combat data for use by other Actors, UI, ETC.

USTRUCT(BlueprintType)
struct FAttackStruct
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Damage = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float ArcAngle = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	float Radius = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
	UAnimMontage* Montage = nullptr;
};

