// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"
#include "BaseUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public :
	virtual void SetHiddenInGame(bool bIsHidden);
	bool IsHiddenInGame() const;
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};