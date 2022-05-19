// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHUDWidget.h"
#include "Asadal/Widget/Screen/ScreenSkillSetWidget.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UMainHUDWidget : public UBaseHUDWidget
{
	GENERATED_BODY()

public :
	virtual void SetPCSkill(uint32 Index, FGameplayAbilitySpec* GameplayAbilitySpec) override;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TSoftObjectPtr<class UScreenSkillSetWidget> ScreenSkillSetWidget;	

private:
	UFUNCTION()
	void __OnSkillSetButtonClickNative(int32 Index);

	UFUNCTION()
	void __OnSwapWeaponButtonClickNative();

	UFUNCTION()
	void __OnAvoidButtonClickNative();
};
