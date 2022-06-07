// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "Asadal/Asadal.h"
#include "Asadal/Character/BaseCharacter.h"
#include "Asadal/Widget/HUD/BaseHUDWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(BaseHUDWidgetClass))
	{
		BaseHUDWidget = CreateWidget<UBaseHUDWidget>(GetWorld(), BaseHUDWidgetClass);
		
		if (BaseHUDWidget.IsValid())
		{
			BaseHUDWidget->AddToViewport();
			BaseHUDWidget->SkillSetButtonClickedEvent.AddDynamic(this, &ABaseHUD::__OnSkillSetButtonClickNative);
			BaseHUDWidget->SwapWeaponChangeClickEvent.AddDynamic(this, &ABaseHUD::__OnSwapWeaponButtonClickNative);
			BaseHUDWidget->AvoidClickEvent.AddDynamic(this, &ABaseHUD::__OnAvoidButtonClickNative);
		}	
	}

	APlayerController* PlayerController = GetOwningPlayerController();

	if(IsValid(PlayerController))
	{
		BaseCharacter = Cast<ABaseCharacter>(PlayerController->GetPawn());
	}
}

void ABaseHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(BaseCharacter.IsValid())
	{
		//여기서 알아서 갱신한다.

		for(uint32 Index = 0; Index < MAX_PC_SKILL_COUNT; ++Index)
		{
			UTexture2D* IconTexture = BaseCharacter->GetAbilityIconByIndex(Index);

			BaseHUDWidget->SetPCSkillIcon(Index, IconTexture);
		}
	}
}

void ABaseHUD::__OnSkillSetButtonClickNative(int32 Index)
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(Index);
	}
}

void ABaseHUD::__OnSwapWeaponButtonClickNative()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryEquipNextWeapon();
	}
}

void ABaseHUD::__OnAvoidButtonClickNative()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAvoid();
	}
}
