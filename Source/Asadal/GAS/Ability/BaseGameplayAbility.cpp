// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGameplayAbility.h"

void UGEExecResult::SetCritical(bool InIsCritical)
{
	bIsCritical = InIsCritical;
}

bool UGEExecResult::IsCritical() const
{
	return bIsCritical;
}

void UGEExecResult::SetDamage(const FGameplayTag& GameplayTag, float Damage)
{
	DamageFromTag.Add(GameplayTag, Damage);
}

float UGEExecResult::GetDamage(const FGameplayTag& GameplayTag) const
{
	if(DamageFromTag.Contains(GameplayTag))
	{
		return *DamageFromTag.Find(GameplayTag);
	}

	return 0.f;
}

UBaseGameplayAbility::UBaseGameplayAbility()
{
	//InstancingPolicy = EGameplayAbilityInstancingPolicy::Type::InstancedPerActor;
}