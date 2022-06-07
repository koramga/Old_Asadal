// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenCharacterStatusWidget.h"
#include "Components/ProgressBar.h"

void UScreenCharacterStatusWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ID_HealthBar")));

	SetHealthPercent(InitHealthBarPercent);
}

void UScreenCharacterStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScreenCharacterStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenCharacterStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScreenCharacterStatusWidget::SetHealthPercent(float Percent)
{
	if(HealthBar.IsValid())
	{
		HealthBar->SetPercent(Percent);
	}
	else
	{
		InitHealthBarPercent = Percent;
	}
}
