// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGActorCue.h"
#include "NiagaraComponent.h"
#include "KRGActorCue_Effect.generated.h"

UCLASS()
class KRGGASTOOLKIT_API AKRGActorCue_Effect : public AKRGActorCue
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AKRGActorCue_Effect();

protected:
	virtual bool Recycle() override;
	virtual bool HandlesEvent(EGameplayCueEvent::Type EventType) const override;
	virtual void HandleGameplayCue(AActor* MyTarget, EGameplayCueEvent::Type EventType, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraComponent* NiagaraComponent;
};
