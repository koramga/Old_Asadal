﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseUserWidget.h"

void UBaseUserWidget::SetHiddenInGame(bool bIsHidden)
{
	if(bIsHidden)
	{
		Super::SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		Super::SetVisibility(ESlateVisibility::Visible);
	}
}

bool UBaseUserWidget::IsHiddenInGame() const
{
	ESlateVisibility SlateVisibility = GetVisibility();

	if(ESlateVisibility::Hidden == SlateVisibility)
	{
		return true;
	}

	return false;
}

void UBaseUserWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UBaseUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseUserWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UBaseUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
