// Fill out your copyright notice in the Description page of Project Settings.


#include "MainScreenWidget.h"

#include "Components/Button.h"
#include "Kismet/KismetMathLibrary.h"

void UMainScreenWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	ButtonTest = Cast<UButton>(GetWidgetFromName(TEXT("BtnTest")));
}

void UMainScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if(ButtonTest.IsValid())
	{
		ButtonTest->OnClicked.AddDynamic(this, &UMainScreenWidget::__OnClickTest);
	}
}

void UMainScreenWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMainScreenWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainScreenWidget::__OnClickTest()
{
	ButtonTest->SetBackgroundColor(FLinearColor::MakeRandomColor());
	UE_LOG(LogTemp, Display, TEXT("OnClickedTest"));
}
