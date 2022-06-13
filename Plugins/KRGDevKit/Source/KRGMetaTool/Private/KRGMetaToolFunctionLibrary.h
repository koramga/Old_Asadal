// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGVariableMetaData.h"
#include "KRGMetaToolFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class KRGMETATOOL_API UKRGMetaToolFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public :
	static TKRGMetaVariable MakeRangeScopeVariable(const TKRGMetaVariable& LMetaVariant, const TKRGMetaVariable& RMetaVariant);
	static TKRGMetaVariable LerpVariable(const TKRGMetaVariable& LMetaVariant, const TKRGMetaVariable& RMetaVariant, float LerpTime);
};
