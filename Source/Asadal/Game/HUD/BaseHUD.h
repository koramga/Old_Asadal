// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API ABaseHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UBaseHUDWidget>		BaseHUDWidgetClass;
	TSoftObjectPtr<class UBaseHUDWidget>	BaseHUDWidget;

protected:
	virtual void BeginPlay() override;
};