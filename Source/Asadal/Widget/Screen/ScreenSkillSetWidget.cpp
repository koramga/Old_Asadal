// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenSkillSetWidget.h"
#include "ScreenButtonWidget.h"
#include "Asadal/Asadal.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"

void UScreenSkillSetWidget::SetPCSkill(int32 Index, FGameplayAbilitySpec* GameplayAbilitySpec)
{
	if(PCSkillButtons.Num() > Index)
	{
		if(nullptr == GameplayAbilitySpec)
		{
			PCSkillButtons[Index]->SetIconTexture(nullptr);
		}
		else
		{
			UBaseGameplayAbility* BaseGameplayAbility = Cast<UBaseGameplayAbility>(GameplayAbilitySpec->Ability);

			if(IsValid(BaseGameplayAbility))
			{
				PCSkillButtons[Index]->SetIconTexture(BaseGameplayAbility->GetIconTexture());
			}
		}		
	}
}

void UScreenSkillSetWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	for(int i = 0; i < MAX_PC_SKILL_COUNT; ++i)
	{
		FString ButtonName = FString::Printf(TEXT("ButtonPCSkill%d"), i);

		PCSkillButtons.Add(Cast<UScreenButtonWidget>(GetWidgetFromName(FName(ButtonName))));	
	}
	
	WeaponSwapButton = Cast<UScreenButtonWidget>(GetWidgetFromName(FName(TEXT("ID_ButtonPCSwapWeapon"))));
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