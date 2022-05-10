// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PCController.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API APCController : public APlayerController
{
	GENERATED_BODY()

public :
	APCController();

protected:
	virtual void SetupInputComponent() override;
	virtual void OnPossess(APawn* InPawn) override;

protected:
	class APCCharacter* PCCharacter;
	
private :
	void __InputMoveRight(float Value);
	void __InputMoveForward(float Value);

	void __InputPressedPCSkill0();
	void __InputPressedPCSkill1();
	void __InputPressedPCSkill2();
	void __InputPressedPCSkill3();
	void __InputPressedPCSkill4();
	
};


