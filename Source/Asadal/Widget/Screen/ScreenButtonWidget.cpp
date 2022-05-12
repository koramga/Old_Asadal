// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenButtonWidget.h"

#include "Components/Image.h"

void UScreenButtonWidget::SetIconTexture(UTexture2D* Texture)
{
	if(nullptr == Texture
		|| false == IsValid(Texture))
	{
		MainIcon->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		if(MainIcon.IsValid())
		{
			MainIcon->SetVisibility(ESlateVisibility::Visible);
			MainIcon->SetBrushFromTexture(Texture);
		}		
	}
}

void UScreenButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	MainButton = Cast<UButton>(GetWidgetFromName(TEXT("ID_MainButton")));
	MainIcon = Cast<UImage>(GetWidgetFromName(TEXT("ID_ButtonIcon")));

	if(IsValid(InitIcon))
	{
		MainIcon->SetBrushFromTexture(InitIcon);
	}
}

void UScreenButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(MainButton.IsValid())
	{
		MainButton->OnClicked.AddDynamic(this, &UScreenButtonWidget::__OnButtonClickedNative);
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
	OnClicked.Broadcast(this);
}