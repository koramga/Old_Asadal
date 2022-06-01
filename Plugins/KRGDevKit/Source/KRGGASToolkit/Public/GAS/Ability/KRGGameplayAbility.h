// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/GEExecutionCalculation/ExecResult/KRGGEExecResult.h"
#include "KRGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASTOOLKIT_API UKRGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void EndAbility(bool bWasCancelled = false, bool bReplicateEndAbility = true);

	
public :
	bool HasTagActivationRequiredTags(FGameplayTag GameplayTag);
	const TArray<UKRGGEExecResult*>& GetAbilityGEExecInfos() const;
	void AddAbilityGEExecInfo(UKRGGEExecResult* GEExecResult);

UPROPERTY()
	TArray<UKRGGEExecResult*>			AbilityGEExecResults;
};
