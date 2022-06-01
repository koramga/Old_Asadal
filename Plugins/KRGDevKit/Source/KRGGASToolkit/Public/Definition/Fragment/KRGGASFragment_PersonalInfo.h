// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASFragment_PersonalInfo.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASTOOLKIT_API UKRGGASFragment_PersonalInfo : public UKRGGASFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName		Name;
};
