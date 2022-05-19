// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UBaseHUDWidget>		BaseHUDWidgetClass;
	TSoftObjectPtr<class UBaseHUDWidget>	BaseHUDWidget;
	TSoftObjectPtr<class APCCharacter>		PCCharacter;

private:
	UFUNCTION()
	void __OnSkillSetButtonClickNative(int32 Index);

	UFUNCTION()
	void __OnSwapWeaponButtonClickNative();

	UFUNCTION()
	void __OnAvoidButtonClickNative();
};