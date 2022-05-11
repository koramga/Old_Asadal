// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"

void UBasicGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if(IsValid(AnimMontage)
		&& IsValid(GameplayEffectClass))
	{
		PlayMontageAndWait = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, AnimMontage, PlayRate, NAME_None, true, 1.f, 0.f);

		if(PlayMontageAndWait.IsValid())
		{ 
			PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UBasicGameplayAbility::__OnBlendOutNative);
			PlayMontageAndWait->OnCancelled.AddDynamic(this, &UBasicGameplayAbility::__OnCancelledNative);
			PlayMontageAndWait->OnCompleted.AddDynamic(this, &UBasicGameplayAbility::__OnCompleteNative);
			PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UBasicGameplayAbility::__OnInterruptedNative);

			WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitGameplayEventTag);

			if(WaitGameplayEvent.IsValid())
			{
				WaitGameplayEvent->EventReceived.AddDynamic(this, &UBasicGameplayAbility::__OnWaitGameplayEventReceivedNative);
				
				PlayMontageAndWait->Activate();
				WaitGameplayEvent->Activate();
			}			
		}
	}
}

void UBasicGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UBasicGameplayAbility::__OnCompleteNative()
{
	Super::EndAbility();
}

void UBasicGameplayAbility::__OnBlendOutNative()
{
	Super::EndAbility();
}

void UBasicGameplayAbility::__OnInterruptedNative()
{
	Super::EndAbility();
}

void UBasicGameplayAbility::__OnCancelledNative()
{
	Super::EndAbility();
}

void UBasicGameplayAbility::__OnWaitGameplayEventReceivedNative(FGameplayEventData Payload)
{
	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(Payload.Target));

	BP_ApplyGameplayEffectToTarget(AbilityTargetDataHandle, GameplayEffectClass);
}
