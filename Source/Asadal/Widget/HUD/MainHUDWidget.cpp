// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUDWidget.h"
#include "Asadal/Widget/Screen/ScreenSkillSetWidget.h"

void UMainHUDWidget::SetPCSkillIcon(uint32 Index, UTexture2D* IconTexture)
{
	Super::SetPCSkillIcon(Index, IconTexture);

	if(ScreenSkillSetWidget.IsValid())
	{
		ScreenSkillSetWidget->SetPCSkillIcon(Index, IconTexture);
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
		ScreenSkillSetWidget->AvoidClickEvent.AddDynamic(this, &UMainHUDWidget::__OnAvoidButtonClickNative);
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

void UMainHUDWidget::__OnAvoidButtonClickNative()
{
	AvoidClickEvent.Broadcast();
}
