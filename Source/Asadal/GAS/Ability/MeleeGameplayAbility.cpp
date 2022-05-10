// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeGameplayAbility.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AbilitySystemBlueprintLibrary.h"

void UMeleeGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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
			PlayMontageAndWait->OnBlendOut.AddDynamic(this, &UMeleeGameplayAbility::__OnBlendOutNative);
			PlayMontageAndWait->OnCancelled.AddDynamic(this, &UMeleeGameplayAbility::__OnCancelledNative);
			PlayMontageAndWait->OnCompleted.AddDynamic(this, &UMeleeGameplayAbility::__OnCompleteNative);
			PlayMontageAndWait->OnInterrupted.AddDynamic(this, &UMeleeGameplayAbility::__OnInterruptedNative);

			WaitGameplayEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, HitGameplayEventTag);

			if(WaitGameplayEvent.IsValid())
			{
				WaitGameplayEvent->EventReceived.AddDynamic(this, &UMeleeGameplayAbility::__OnWaitGameplayEventReceivedNative);
				
				PlayMontageAndWait->Activate();
				WaitGameplayEvent->Activate();
			}			
		}
	}
}

void UMeleeGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UMeleeGameplayAbility::__OnCompleteNative()
{
	Super::EndAbility();
}

void UMeleeGameplayAbility::__OnBlendOutNative()
{
	Super::EndAbility();
}

void UMeleeGameplayAbility::__OnInterruptedNative()
{
	Super::EndAbility();
}

void UMeleeGameplayAbility::__OnCancelledNative()
{
	Super::EndAbility();
}

void UMeleeGameplayAbility::__OnWaitGameplayEventReceivedNative(FGameplayEventData Payload)
{
	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle = UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(const_cast<AActor*>(Payload.Target));

	BP_ApplyGameplayEffectToTarget(AbilityTargetDataHandle, GameplayEffectClass);
}
