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
	TArray<FKRGGASFragmentAbilityHandle>	AttackAbilityFragmentHandles;
	FKRGGASFragmentAbilityHandle			HitAbilityFragmentHandle;
	FKRGGASFragmentAbilityHandle			AvoidAbilityFragmentHandle;

	void Clear()
	{
		AttackAbilityFragmentHandles.Empty();
		HitAbilityFragmentHandle.Clear();
		AvoidAbilityFragmentHandle.Clear();
	}
};

UCLASS(ClassGroup=AbilitySystem, hidecategories=(Object,LOD,Lighting,Transform,Sockets,TextureStreaming), editinlinenew, meta=(BlueprintSpawnableComponent))
class ASADAL_API UGASComponent : public UKRGAbilitySystemComponent
{
	GENERATED_BODY()

public :
	//bool GEToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayTag& EventTag);
	//void SetGEToTargetLatent(bool InIsLatentEventToTarget);
	void GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs);
	const FGameplayAbilityActionGroup* GetActivateAbilityActionGroup() const;
	bool TryAvoidAbilityFromActionGroup();
	bool TryHitAbilityFromActionGroup();
	bool TryAttackAbilityFromActionGroup(int32 ElementIndex);

protected:
	virtual bool CanGEExec(UAbilitySystemComponent* AbilitySystemComponent, UAbilitySystemComponent* TargetAbilitySystemComponent) override;
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual bool IsCriticalAbility() override;
	virtual void OnUpdateActivateFragmentAbility() override;
	virtual void OnUpdateActivateFragmentAttributeSet() override;
	
protected:
	FGameplayAbilityActionGroup						ActivateAbilityActionGroup;
};
