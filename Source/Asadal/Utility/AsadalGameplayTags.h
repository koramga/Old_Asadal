// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AsadalGameplayTags.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UAsadalGameplayTags : public UObject
{
	GENERATED_BODY()
	
public :
	static const FGameplayTag DeathGameplayTag;
	static const FGameplayTag EventAttackBasicTag;
};
