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

UTexture2D* UBaseGameplayAbility::GetIconTexture() const
{
	return IconTexture;
}

void UBaseGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UBaseGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AbilityGEExecResults.Empty();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBaseGameplayAbility::EndAbility(bool bWasCancelled, bool bReplicateEndAbility)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UBaseGameplayAbility::HasTagActivationRequiredTags(FGameplayTag GameplayTag)
{
	return ActivationRequiredTags.HasTag(GameplayTag);
}

const TArray<UGEExecResult*>& UBaseGameplayAbility::GetAbilityGEExecInfos() const
{
	return AbilityGEExecResults;
}

void UBaseGameplayAbility::AddAbilityGEExecInfo(UGEExecResult* GEExecResult)
{
	AbilityGEExecResults.Add(GEExecResult);
}