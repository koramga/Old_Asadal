// Fill out your copyright notice in the Description page of Project Settings.


#include "PCController.h"

#include "Asadal/Character/PC/PCCharacter.h"
#include "Asadal/Game/CheatManager/BaseCheatManager.h"

APCController::APCController()
{
	CheatClass = UBaseCheatManager::StaticClass();
}

void APCController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("MoveForward", this, &APCController::__InputMoveForward);
	InputComponent->BindAxis("MoveRight", this, &APCController::__InputMoveRight);
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