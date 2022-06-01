// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Fragment/KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASDefinition.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DefaultToInstanced)
class KRGGASTOOLKIT_API UKRGGASDefinition : public UDataAsset
{
	GENERATED_BODY()

public :
	UKRGGASDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced)
	TArray<UKRGGASFragment*>	Fragments;

public :
	UKRGGASFragment* FindFragmentByClass(TSubclassOf<UKRGGASFragment> FragmentClass);
};
