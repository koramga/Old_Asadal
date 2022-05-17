// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASComponent.generated.h"

/**
 * 
 */

struct FGEToTargetEventItem
{
	TSoftObjectPtr<AActor>		Actor;
	FGameplayTag				EventTag = FGameplayTag::EmptyTag;

	FGEToTargetEventItem() {}

	FGEToTargetEventItem(AActor* Actor, const FGameplayTag& EventTag)
		: Actor(Actor), EventTag(EventTag) {}
};

struct FGameplayAbilityActionGroup
{
	TArray<FGameplayAbilitySpecHandle>	AttackAbilitiesSpecHandles;
	FGameplayAbilitySpecHandle			HitAbilitySpecHandle;
	FGameplayAbilitySpecHandle			AvoidAbilitySpecHandle;
};

UCLASS()
class ASADAL_API UGASComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public :
	void GEToTarget(AActor* Actor, const FGameplayTag& EventTag);
	void SetGEToTargetLatent(bool InIsLatentEventToTarget);
	void GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs);
	void SetActivateAbilityActionGroup(const FGameplayTag& GameplayTag);
	const FGameplayAbilityActionGroup* GetActivateAbilityActionGroup() const;

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;

protected:
	TArray<FGEToTargetEventItem>	GEToTargetLatentEventItems;
	bool	bIsLatentEventToTarget = false;

	//Base도 Ability안에 포함할 수 있다.
	TMap<FGameplayTag, FGameplayAbilityActionGroup>	AbilityActionGroupMap;
	const FGameplayAbilityActionGroup*				ActivateAbilityActionGroup = nullptr;
};
