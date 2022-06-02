// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GAS/Ability/KRGGameplayAbility.h"
#include "GAS/GEExecutionCalculation/ExecResult/KRGGEExecResult.h"
#include "UObject/Object.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
*/
UCLASS()
class ASADAL_API UGEExecResult : public UKRGGEExecResult
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
};
