// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "Asadal/Character/PC/PCCharacter.h"
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

	PCCharacter = Cast<APCCharacter>(InPawn);
}

void APCController::__InputMoveForward(float Value)
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->InputMoveForward(Value);
	}
}

void APCController::__InputMoveRight(float Value)
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->InputMoveRight(Value);
	}
}

void APCController::__InputPressedPCSkill0()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryActivateSkillByIndex(0);
	}
}

void APCController::__InputPressedPCSkill1()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryActivateSkillByIndex(1);
	}
}

void APCController::__InputPressedPCSkill2()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryActivateSkillByIndex(2);
	}
}

void APCController::__InputPressedPCSkill3()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryActivateSkillByIndex(3);
	}
}

void APCController::__InputPressedPCSkill4()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryActivateSkillByIndex(4);
	}
}

void APCController::__InputSwapWeapon()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryEquipNextWeapon();
	}
}

void APCController::__InputPressedDash()
{
	if(IsValid(PCCharacter))
	{
		PCCharacter->TryDash();
	}
}
