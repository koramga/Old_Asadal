// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "GASComponent.generated.h"

/**
 * 
 */

struct FGameplayAbilityActionGroup
{
	TArray<FGameplayAbilitySpecHandle>	AttackAbilitiesSpecHandles;
	FGameplayAbilitySpecHandle			HitAbilitySpecHandle;
	FGameplayAbilitySpecHandle			AvoidAbilitySpecHandle;
	int32 AttackElementIndex = -1;
};

UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class ASADAL_API UGASComponent : public UKRGAbilitySystemComponent
{
	GENERATED_BODY()

public :
	//bool GEToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayTag& EventTag);
	//void SetGEToTargetLatent(bool InIsLatentEventToTarget);
	void GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs);
	void SetActivateAbilityActionGroup(const FGameplayTag& GameplayTag);
	const FGameplayAbilityActionGroup* GetActivateAbilityActionGroup() const;
	bool TryAvoidAbilityFromActionGroup();
	bool TryHitAbilityFromActionGroup();
	bool TryAttackAbilityFromActionGroup(int32 ElementIndex);

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual bool IsCriticalAbility() override;
	
protected:
	//Base도 Ability안에 포함할 수 있다.
	TMap<FGameplayTag, FGameplayAbilityActionGroup>	AbilityActionGroupMap;
	FGameplayAbilityActionGroup*					ActivateAbilityActionGroup = nullptr;
};
