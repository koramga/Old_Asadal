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


UCLASS()
class ASADAL_API UGASComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public :
	void GEToTarget(AActor* Actor, const FGameplayTag& EventTag);
	void SetGEToTargetLatent(bool InIsLatentEventToTarget);
	void GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs);

protected:
	TArray<FGEToTargetEventItem>	GEToTargetLatentEventItems;
	bool	bIsLatentEventToTarget = false;
};
