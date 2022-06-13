// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KRGBTBlackboardKeys.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGBTBlackboardKeys : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public :
	static const FName TraceRangeKey;
	static const FName TraceTargetKey;
	static const FName IsFollowTraceTargetKey;
	static const FName FollowTraceTargetDeltaRangeKey;
};
