// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "UObject/Object.h"
#include "ScreenNPCStatusWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UScreenNPCStatusWidget : public UBaseScreenWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public :
	void SetHealthPercent(float Percent);

protected:
	TSoftObjectPtr<class UProgressBar>		HealthBar;
	float									InitHealthBarPercent = 1.f;
};
