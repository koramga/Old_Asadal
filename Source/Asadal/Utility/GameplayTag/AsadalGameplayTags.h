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
	static const FGameplayTag StateGameplayTag;
	static const FGameplayTag AttackStateGameplayTag;
	static const FGameplayTag HitStateGameplayTag;
	static const FGameplayTag DeathStateGameplayTag;
	static const FGameplayTag ActionGameplayTag;
	static const FGameplayTag DeathActionGameplayTag;
	static const FGameplayTag HitActionGameplayTag;
	static const FGameplayTag AttackActionGameplayTag;
	static const FGameplayTag AvoidGameplayTag;
	static const FGameplayTag AbilityGameplayTag;
	static const FGameplayTag AbilityOneHandAxeTag;
	static const FGameplayTag AbilityOneHandMaceTag;
	static const FGameplayTag AbilityOneHandShieldTag;
	static const FGameplayTag AbilityOneHandSwordTag;
	static const FGameplayTag AbilityTwinHandBladeTag;
	static const FGameplayTag AbilityTwinHandDaggerTag;
	static const FGameplayTag AbilityTwoHandGreatswordTag;
	static const FGameplayTag AbilityTwoHandShieldTag;
	static const FGameplayTag BaseAbilityGameplayTag;
	static const FGameplayTag EventAttackBasicTag;
	static const FGameplayTag ItemWeaponTag;
	static const FGameplayTag ItemOneHandAxeTag;
	static const FGameplayTag ItemOneHandMaceTag;
	static const FGameplayTag ItemOneHandShieldTag;
	static const FGameplayTag ItemOneHandSwordTag;
	static const FGameplayTag ItemTwinHandBladeTag;
	static const FGameplayTag ItemTwinHandDaggerTag;
	static const FGameplayTag ItemTwoHandGreatswordTag;
	static const FGameplayTag ItemTwoHandShieldTag;
	static const FGameplayTag GameTimeDilationTag;
	static const FGameplayTag GameTimeDilationStrikeTag;

public :
	static int32 GetDilationPriority(const FGameplayTag& GameplayTag);
	static FGameplayTag GetAbilityGameplayTagFromItem(const FGameplayTag& ItemGameplayTag);
};
