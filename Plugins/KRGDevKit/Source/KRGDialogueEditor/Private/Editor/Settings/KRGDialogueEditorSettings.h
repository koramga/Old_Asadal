// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "KRGDialogueEditorSettings.generated.h"

/**
 * 
 */
UCLASS()
class KRGDIALOGUEEDITOR_API UKRGDialogueEditorSettings : public UObject
{
	GENERATED_BODY()

public :
	UKRGDialogueEditorSettings();
	virtual ~UKRGDialogueEditorSettings();

	UPROPERTY(EditDefaultsOnly, Category="AutoArrange")
	float OptimalDistance;
};
