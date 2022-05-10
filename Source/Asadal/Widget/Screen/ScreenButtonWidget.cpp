// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenButtonWidget.h"

void UScreenButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	MainButtonNative = Cast<UButton>(GetWidgetFromName(TEXT("MainButton")));
}

void UScreenButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(MainButtonNative.IsValid())
	{
		MainButtonNative->OnClicked.AddDynamic(this, &UScreenButtonWidget::__OnButtonClickedNative);
	}
}

void UScreenButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScreenButtonWidget::__OnButtonClickedNative()
{
	OnClicked.Broadcast();
}