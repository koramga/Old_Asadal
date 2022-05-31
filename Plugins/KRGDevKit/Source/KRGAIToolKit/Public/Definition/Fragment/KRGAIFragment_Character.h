// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGAIFragment.h"
#include "KRGAIFragment_Character.generated.h"

/**
 * 
 */
UCLASS()
class KRGAITOOLKIT_API UKRGAIFragment_Character : public UKRGAIFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName		CharacterName;
};
