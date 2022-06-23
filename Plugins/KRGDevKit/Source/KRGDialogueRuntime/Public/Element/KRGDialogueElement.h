// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KRGDialogueElement.generated.h"

/**
 * 
 */

class UKRGDialogueGraph;

UCLASS()
class KRGDIALOGUERUNTIME_API UKRGDialogueElement : public UObject
{
	GENERATED_BODY()

public :
	UKRGDialogueElement();
	virtual ~UKRGDialogueElement();
	
public :
	void SetGraph(UKRGDialogueGraph* InGraph);
	UKRGDialogueGraph* GetGraph() const;

protected:
	UPROPERTY()
	class UKRGDialogueGraph*	Graph;
};
