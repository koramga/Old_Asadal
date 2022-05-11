﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Character/BaseCharacter.h"
#include "GameFramework/Character.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ASADAL_API ANPCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data) override;
	virtual void UpdateDeath(bool bIsDeath) override;
	void UpdateStatusWidgetOnHealth();
	
protected:
	TSoftObjectPtr<class UScreenNPCStatusWidget>	ScreenNPCStatusWidget;
};
