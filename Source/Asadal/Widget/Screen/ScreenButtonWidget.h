// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "Components/Button.h"
#include "ScreenButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UScreenButtonWidget : public UBaseScreenWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TSoftObjectPtr<UButton>	MainButtonNative;

public :
	FOnButtonClickedEvent OnClicked;

private:
	UFUNCTION()
	void __OnButtonClickedNative();
};
