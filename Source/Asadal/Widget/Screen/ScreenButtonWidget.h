// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "Components/Button.h"
#include "ScreenButtonWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScreenButtonClickedEvent, class UScreenButtonWidget*, ScreenButtonWidget);

UCLASS()
class ASADAL_API UScreenButtonWidget : public UBaseScreenWidget
{
	GENERATED_BODY()

public :
	void SetIconTexture(UTexture2D* Texture);
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TSoftObjectPtr<UButton>			MainButton;
	TSoftObjectPtr<class UImage>	MainIcon;

public :
	FOnScreenButtonClickedEvent OnClicked;

private:
	UFUNCTION()
	void __OnButtonClickedNative();
};
