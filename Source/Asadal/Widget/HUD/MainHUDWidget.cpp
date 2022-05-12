// Fill out your copyright notice in the Description page of Project Settings.


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

	if(ScreenSkillSetWidget.IsValid())
	{
		ScreenSkillSetWidget->SkillSetButtonClickedEvent.AddDynamic(this, &UMainHUDWidget::__OnSkillSetButtonClickNative);
		ScreenSkillSetWidget->SwapWeaponChangeClickEvent.AddDynamic(this, &UMainHUDWidget::__OnSwapWeaponButtonClickNative);
	}
}

void UMainHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainHUDWidget::__OnSkillSetButtonClickNative(int32 Index)
{
	SkillSetButtonClickedEvent.Broadcast(Index);
}

void UMainHUDWidget::__OnSwapWeaponButtonClickNative()
{
	SwapWeaponChangeClickEvent.Broadcast();
}
