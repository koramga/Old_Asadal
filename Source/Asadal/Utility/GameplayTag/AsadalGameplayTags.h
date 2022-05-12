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
	static const FGameplayTag ObjectWeaponTag;
	static const FGameplayTag OneHandAxeTag;
	static const FGameplayTag OneHandMaceTag;
	static const FGameplayTag OneHandShieldTag;
	static const FGameplayTag OneHandSwordTag;
	static const FGameplayTag TwinHandBladeTag;
	static const FGameplayTag TwinHandDaggerTag;
	static const FGameplayTag TwoHandGreatswordTag;
	static const FGameplayTag TwoHandShieldTag;
	
};
