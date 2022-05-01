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
	
};
