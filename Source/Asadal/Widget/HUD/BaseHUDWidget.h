// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "Asadal/Widget/BaseUserWidget.h"
#include "Asadal/Widget/Screen/ScreenSkillSetWidget.h"
#include "BaseHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseHUDWidget : public UBaseUserWidget
{
	GENERATED_BODY()

public :
	virtual void SetPCSkillIcon(uint32 Index, UTexture2D* IconTexture);

public :
	FOnSkillSetButtonClickedEvent	SkillSetButtonClickedEvent;
	FOnScreenSkillButtonClickEvent	SwapWeaponChangeClickEvent;
	FOnScreenSkillButtonClickEvent	AvoidClickEvent;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
