// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "KORGameplayCueManager.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASTOOLKIT_API UKORGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()

protected:
	virtual bool ShouldAsyncLoadRuntimeObjectLibraries() const override;
	virtual bool ShouldSyncLoadRuntimeObjectLibraries() const override;
};
