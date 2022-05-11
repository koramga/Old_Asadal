// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameplayAbility.h"
#include "GameplayTagContainer.h"
#include "BasicGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBasicGameplayAbility : public UBaseGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	UAnimMontage*	AnimMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	FGameplayTag	HitGameplayEventTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	float			PlayRate = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	TSoftObjectPtr<class UAbilityTask_PlayMontageAndWait>	PlayMontageAndWait;
	TSoftObjectPtr<class UAbilityTask_WaitGameplayEvent>	WaitGameplayEvent;

private:
	UFUNCTION()
	void __OnCompleteNative();
	UFUNCTION()
	void __OnBlendOutNative();
	UFUNCTION()
	void __OnInterruptedNative();
	UFUNCTION()
	void __OnCancelledNative();
	UFUNCTION()
	void __OnWaitGameplayEventReceivedNative(FGameplayEventData Payload);
};
