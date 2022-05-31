// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Fragment/KRGAIFragment.h"
#include "KRGAIDefinition.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, Const, Abstract)
class KRGAITOOLKIT_API UKRGAIDefinition : public UObject
{
	GENERATED_BODY()

public :
	UKRGAIDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<UKRGAIFragment*>	Fragments;

public :
	UKRGAIFragment* FindFragmentByClass(TSubclassOf<UKRGAIFragment> FragmentClass);
};
