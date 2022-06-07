﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Definition/Fragment/KRGGASFragment.h"
#include "KRGGASFragment_BTAbilities.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FKRGGASBTAbilityInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer					ActivateGameplayTagContainer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UKRGGameplayAbility>	AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TRange<float>							AbilityDistance;
};

UCLASS()
class KRGGASBT_API UKRGGASFragment_BTAbilities : public UKRGGASFragment
{
	GENERATED_BODY()
};
