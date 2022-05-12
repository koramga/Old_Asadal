// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"

#include "Asadal/Asadal.h"
#include "Asadal/Character/PC/PCCharacter.h"
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
		}	
	}

	APlayerController* PlayerController = GetOwningPlayerController();

	if(IsValid(PlayerController))
	{
		PCCharacter = Cast<APCCharacter>(PlayerController->GetPawn());
	}
}

void ABaseHUD::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(PCCharacter.IsValid())
	{
		//여기서 알아서 갱신한다.

		for(uint32 Index = 0; Index < MAX_PC_SKILL_COUNT; ++Index)
		{
			FGameplayAbilitySpec* GameplayAbilitySpec = PCCharacter->GetPCSkillAbilitySpecByIndex(Index);

			BaseHUDWidget->SetPCSkill(Index, GameplayAbilitySpec);
		}
		
		
		//UE_LOG(LogTemp, Display, TEXT("Has Skill <%d>"), PCCharacter->HasSkill(0));
	}
}

void ABaseHUD::__OnSkillSetButtonClickNative(int32 Index)
{
	if(PCCharacter.IsValid())
	{
		PCCharacter->TryActivateSkillByIndex(Index);
	}
}

void ABaseHUD::__OnSwapWeaponButtonClickNative()
{
	if(PCCharacter.IsValid())
	{
		PCCharacter->TryEquipNextWeapon();
	}
}
