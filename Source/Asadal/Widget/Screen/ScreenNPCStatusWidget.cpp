// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenNPCStatusWidget.h"
#include "Components/ProgressBar.h"

void UScreenNPCStatusWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	HealthBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ID_HealthBar")));

	SetHealthPercent(InitHealthBarPercent);
}

void UScreenNPCStatusWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScreenNPCStatusWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenNPCStatusWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScreenNPCStatusWidget::SetHealthPercent(float Percent)
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

