// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCueActor_Base.h"


// Sets default values
AGameplayCueActor_Base::AGameplayCueActor_Base()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

bool AGameplayCueActor_Base::HandlesEvent(EGameplayCueEvent::Type EventType) const
{
	return Super::HandlesEvent(EventType);
}

void AGameplayCueActor_Base::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);
}