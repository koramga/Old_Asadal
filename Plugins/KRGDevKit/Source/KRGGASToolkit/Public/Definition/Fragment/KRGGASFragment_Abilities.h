// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASFragment_Abilities.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FKRGGASAbilityInfo
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer					ActivateGameplayTagContainer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D*								IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UKRGGameplayAbility>	AbilityClass;
};

UCLASS()
class KRGGASTOOLKIT_API UKRGGASFragment_Abilities : public UKRGGASFragment
{
	GENERATED_BODY()

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKRGGASAbilityInfo>	KRGGASAbilityInfos;
};
