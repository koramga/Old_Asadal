// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Cue/Actor/KRGActorCue_Effect.h"


// Sets default values
AKRGActorCue_Effect::AKRGActorCue_Effect()
{
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraEffect"));
	
	SetRootComponent(NiagaraComponent);

	PrimaryActorTick.bStartWithTickEnabled = false;
	bAutoDestroyOnRemove = true;

	//Recycle();
}

bool AKRGActorCue_Effect::Recycle()
{
	return Super::Recycle();
}

bool AKRGActorCue_Effect::HandlesEvent(EGameplayCueEvent::Type EventType) const
{
	return EGameplayCueEvent::Executed == EventType;
}

void AKRGActorCue_Effect::HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType,
	const FGameplayCueParameters& Parameters)
{
	Super::HandleGameplayCue(MyTarget, EventType, Parameters);

	check(EventType == EGameplayCueEvent::Executed);

	if(IsValid(NiagaraComponent))
	{
		SetActorLocation(MyTarget->GetActorLocation());
		NiagaraComponent->Activate(true);
	}
}
