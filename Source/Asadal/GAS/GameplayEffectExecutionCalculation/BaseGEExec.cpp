// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGEExec.h"
#include "../AttributeSet/LifeAttributeSet.h"

UBaseGEExec::UBaseGEExec()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(ULifeAttributeSet, Health, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(ULifeAttributeSet, Mana, Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(ManaDef);
}

void UBaseGEExec::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                         FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
}
