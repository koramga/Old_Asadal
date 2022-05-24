// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "BaseGEExec.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseGEExec : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public :
	UBaseGEExec();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

protected:
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Mana)
};
