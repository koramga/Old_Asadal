// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/Ability/KRGGameplayAbility.h"
#include "UObject/Object.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
*/
UCLASS()
class ASADAL_API UGEExecResult : public UObject
{
	GENERATED_BODY()

public :
	void SetCritical(bool InIsCritical);	 
	bool IsCritical() const;
	void SetDamage(const FGameplayTag& GameplayTag, float Damage);
	float GetDamage(const FGameplayTag& GameplayTag) const;

private:
	bool bIsCritical = false;
	TMap<FGameplayTag, float> DamageFromTag;
};


UCLASS()
class ASADAL_API UBaseGameplayAbility : public UKRGGameplayAbility
{
	GENERATED_BODY()

public :
	UBaseGameplayAbility();

public :
	UTexture2D* GetIconTexture() const;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void EndAbility(bool bWasCancelled = false, bool bReplicateEndAbility = true);

public :
	bool HasTagActivationRequiredTags(FGameplayTag GameplayTag);
	const TArray<UGEExecResult*>& GetAbilityGEExecInfos() const;
	void AddAbilityGEExecInfo(UGEExecResult* GEExecResult);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	UTexture2D*	IconTexture;

	UPROPERTY()
	TArray<UGEExecResult*>			AbilityGEExecResults;

	//TMap<FGameplayEffectContextHandle, FAbilityGEExecInfo>	AbilityGEExecInfoMap;
};
