// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AsadalStructure.generated.h"

USTRUCT(BlueprintType)
struct FTimeDilationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	TimeDilation = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	KeepTime = 0.5f;
};