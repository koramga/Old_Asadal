﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Widget/BaseUserWidget.h"
#include "BaseScreenWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseScreenWidget : public UBaseUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
