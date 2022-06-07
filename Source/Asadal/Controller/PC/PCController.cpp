// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "Asadal/Character/BaseCharacter.h"
#include "Asadal/Character/BaseCharacter.h"
#include "Asadal/Game/CheatManager/BaseCheatManager.h"

APCController::APCController()
{
	CheatClass = UBaseCheatManager::StaticClass();
}

const FTimeDilationSettings& APCController::GetStrikeTimeDilationSettings() const
{
	return StrikeTimeDilationSettings;
}

TSubclassOf<UCameraShakeBase> APCController::GetStrikeCameraShake() const
{
	return  StrikeCameraShake;
}

void APCController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveForward", this, &APCController::__InputMoveForward);
	InputComponent->BindAxis("MoveRight", this, &APCController::__InputMoveRight);
	InputComponent->BindAction("InputPCSkill0",IE_Pressed,  this, &APCController::__InputPressedPCSkill0);
	InputComponent->BindAction("InputPCSkill1", IE_Pressed, this, &APCController::__InputPressedPCSkill1);
	InputComponent->BindAction("InputPCSkill2", IE_Pressed, this, &APCController::__InputPressedPCSkill2);
	InputComponent->BindAction("InputPCSkill3", IE_Pressed, this, &APCController::__InputPressedPCSkill3);
	InputComponent->BindAction("InputPCSkill4", IE_Pressed, this, &APCController::__InputPressedPCSkill4);
	InputComponent->BindAction("InputSwapWeapon", IE_Pressed, this, &APCController::__InputSwapWeapon);
	InputComponent->BindAction("InputDash", IE_Pressed, this, &APCController::__InputPressedDash);
}

void APCController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	BaseCharacter = Cast<ABaseCharacter>(InPawn);
}

void APCController::__InputMoveForward(float Value)
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->InputMoveForward(Value);
	}
}

void APCController::__InputMoveRight(float Value)
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->InputMoveRight(Value);
	}
}

void APCController::__InputPressedPCSkill0()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(0);
	}
}

void APCController::__InputPressedPCSkill1()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(1);
	}
}

void APCController::__InputPressedPCSkill2()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(2);
	}
}

void APCController::__InputPressedPCSkill3()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(3);
	}
}

void APCController::__InputPressedPCSkill4()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAttackAbilityByIndex(4);
	}
}

void APCController::__InputSwapWeapon()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryEquipNextWeapon();
	}
}

void APCController::__InputPressedDash()
{
	if(BaseCharacter.IsValid())
	{
		BaseCharacter->TryAvoid();
	}
}
