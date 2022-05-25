// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GASComponent.generated.h"

/**
 * 
 */

USTRUCT()
struct FGEToTargetEventItem
{
	GENERATED_BODY()

	TSoftObjectPtr<AActor>					Actor;
	TSoftObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;
	FGameplayTag							EventTag = FGameplayTag::EmptyTag;

	FGEToTargetEventItem() {}

	FGEToTargetEventItem(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& EventTag)
		: Actor(AbilitySystemComponent->GetOwner()), AbilitySystemComponent(AbilitySystemComponent), EventTag(EventTag) {}
};

struct FGameplayAbilityActionGroup
{
	TArray<FGameplayAbilitySpecHandle>	AttackAbilitiesSpecHandles;
	FGameplayAbilitySpecHandle			HitAbilitySpecHandle;
	FGameplayAbilitySpecHandle			AvoidAbilitySpecHandle;
	int32 AttackElementIndex = -1;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGEToTargetLatentEvent, const TArray<FGEToTargetEventItem>&, LatentEventItems, bool, bIsCritical);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTagUpdatedEvent, const FGameplayTag&, Tag, bool, TagExists);

UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class ASADAL_API UGASComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public :
	FOnGEToTargetLatentEvent	OnGEToTargetLatentEvent;
	FOnTagUpdatedEvent			OnTagUpdatedEvent;
	
	bool GEToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayTag& EventTag);
	void SetGEToTargetLatent(bool InIsLatentEventToTarget);
	void GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs);
	void SetActivateAbilityActionGroup(const FGameplayTag& GameplayTag);
	const FGameplayAbilityActionGroup* GetActivateAbilityActionGroup() const;
	bool IsCriticalAbilityFromActionGroup();
	bool TryAvoidAbilityFromActionGroup();
	bool TryHitAbilityFromActionGroup();
	bool TryAttackAbilityFromActionGroup(int32 ElementIndex);

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

protected:
	TArray<FGEToTargetEventItem>	GEToTargetLatentEventItems;
	bool	bIsLatentEventToTarget = false;

	//Base도 Ability안에 포함할 수 있다.
	TMap<FGameplayTag, FGameplayAbilityActionGroup>	AbilityActionGroupMap;
	FGameplayAbilityActionGroup*					ActivateAbilityActionGroup = nullptr;
};
