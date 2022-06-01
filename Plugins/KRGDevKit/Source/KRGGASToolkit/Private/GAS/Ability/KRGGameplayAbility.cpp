// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGGASToolkit/Public/GAS/Ability/KRGGameplayAbility.h"


void UKRGGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
										   const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
										   const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UKRGGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	AbilityGEExecResults.Empty();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UKRGGameplayAbility::EndAbility(bool bWasCancelled, bool bReplicateEndAbility)
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

bool UKRGGameplayAbility::HasTagActivationRequiredTags(FGameplayTag GameplayTag)
{
	return ActivationRequiredTags.HasTag(GameplayTag);
}

const TArray<UKRGGEExecResult*>& UKRGGameplayAbility::GetAbilityGEExecInfos() const
{
	return AbilityGEExecResults;
}

void UKRGGameplayAbility::AddAbilityGEExecInfo(UKRGGEExecResult* GEExecResult)
{
	AbilityGEExecResults.Add(GEExecResult);
}