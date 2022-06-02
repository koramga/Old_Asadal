// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenSkillSetWidget.h"
#include "ScreenButtonWidget.h"
#include "Asadal/Asadal.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"

void UScreenSkillSetWidget::SetPCSkillIcon(int32 Index, UTexture2D* IconTexture)
{
	if(PCSkillButtons.Num() > Index)
	{
		PCSkillButtons[Index]->SetIconTexture(IconTexture);
	}
}

void UScreenSkillSetWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	for(int i = 0; i < MAX_PC_SKILL_COUNT; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("ButtonPCSkill%d"), i + 1);

		PCSkillButtons.Add(Cast<UScreenButtonWidget>(GetWidgetFromName(FName(ButtonName))));	
	}
	
	WeaponSwapButton = Cast<UScreenButtonWidget>(GetWidgetFromName(FName(TEXT("ID_ButtonPCSwapWeapon"))));
	AvoidButton = Cast<UScreenButtonWidget>(GetWidgetFromName(FName(TEXT("ButtonPCAvoid"))));
}

void UScreenSkillSetWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for(int i = 0; i < MAX_PC_SKILL_COUNT; ++i)
	{
		if(PCSkillButtons[i].IsValid())
		{
			PCSkillButtons[i]->OnClicked.AddDynamic(this, &UScreenSkillSetWidget::__OnSkillButtonClickNative);
		}
	}

	if(WeaponSwapButton.IsValid())
	{
		WeaponSwapButton->OnClicked.AddDynamic(this, &UScreenSkillSetWidget::__OnWeaponChangeButtonClickNative);
	}

	if(AvoidButton.IsValid())
	{
		AvoidButton->OnClicked.AddDynamic(this, &UScreenSkillSetWidget::__OnAvoidButtonClickNative);
	}
}

void UScreenSkillSetWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UScreenSkillSetWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UScreenSkillSetWidget::__OnSkillButtonClickNative(UScreenButtonWidget* ScreenButtonWidget)
{
	int32 Index = PCSkillButtons.Find(ScreenButtonWidget);

	SkillSetButtonClickedEvent.Broadcast(Index);
}

void UScreenSkillSetWidget::__OnWeaponChangeButtonClickNative(UScreenButtonWidget* ScreenButtonWidget)
{
	SwapWeaponChangeClickEvent.Broadcast();
}

void UScreenSkillSetWidget::__OnAvoidButtonClickNative(UScreenButtonWidget* ScreenButtonWidget)
{
	AvoidClickEvent.Broadcast();
}
