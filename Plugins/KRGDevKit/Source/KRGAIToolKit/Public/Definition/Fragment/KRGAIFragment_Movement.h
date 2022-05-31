// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGAIFragment.h"
#include "KRGAIFragment_Movement.generated.h"

/**
 * 
 */
UCLASS()
class KRGAITOOLKIT_API UKRGAIFragment_Movement : public UKRGAIFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Speed = 0.f;
};
