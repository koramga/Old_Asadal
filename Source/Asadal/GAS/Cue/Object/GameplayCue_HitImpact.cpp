// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCue_HitImpact.h"

bool UGameplayCue_HitImpact::HandlesEvent(EGameplayCueEvent::Type EventType) const
{
	return (EventType == EGameplayCueEvent::Executed);
}

void UGameplayCue_HitImpact::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
	
	check(EventType == EGameplayCueEvent::Executed);
}

bool UGameplayCue_HitImpact::OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	return Super::OnActive_Implementation(MyTarget, Parameters);
}

bool UGameplayCue_HitImpact::OnExecute_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	return Super::OnExecute_Implementation(MyTarget, Parameters);
}

bool UGameplayCue_HitImpact::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) const
{
	return Super::OnRemove_Implementation(MyTarget, Parameters);
}

bool UGameplayCue_HitImpact::WhileActive_Implementation(AActor* MyTarget,
                                                        const FGameplayCueParameters& Parameters) const
{
	return Super::WhileActive_Implementation(MyTarget, Parameters);
}
