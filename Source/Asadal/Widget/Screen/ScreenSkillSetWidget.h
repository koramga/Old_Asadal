// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseScreenWidget.h"
#include "GameplayAbilitySpec.h"
#include "UObject/Object.h"
#include "ScreenSkillSetWidget.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkillSetButtonClickedEvent, int32, Index);

UCLASS()
class ASADAL_API UScreenSkillSetWidget : public UBaseScreenWidget
{
	GENERATED_BODY()
	
public :
	void SetPCSkill(int32 Index, FGameplayAbilitySpec* GameplayAbilitySpec);

public :
	FOnSkillSetButtonClickedEvent	SkillSetButtonClickedEvent;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	TArray<TSoftObjectPtr<class UScreenButtonWidget>>	PCSkillButtons;

private:
	UFUNCTION()
	void __OnSkillButtonClickNative(UScreenButtonWidget* ScreenButtonWidget);
};
