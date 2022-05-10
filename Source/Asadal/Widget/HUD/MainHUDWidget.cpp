﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "Asadal/Widget/Screen/ScreenSkillSetWidget.h"

void UMainHUDWidget::SetPCSkill(uint32 Index, FGameplayAbilitySpec* GameplayAbilitySpec)
{
	Super::SetPCSkill(Index, GameplayAbilitySpec);

	if(ScreenSkillSetWidget.IsValid())
	{
		ScreenSkillSetWidget->SetPCSkill(Index, GameplayAbilitySpec);
	}
}

void UMainHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	ScreenSkillSetWidget = Cast<UScreenSkillSetWidget>(GetWidgetFromName(FName("ID_ScreenSkillSet")));
}

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
