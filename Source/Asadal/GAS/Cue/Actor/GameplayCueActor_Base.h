// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Cue/Actor/KRGActorCue.h"

#include "GameplayCueActor_Base.generated.h"

UCLASS()
class ASADAL_API AGameplayCueActor_Base : public AKRGActorCue
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGameplayCueActor_Base();

protected:
	virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const override;
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;
};
