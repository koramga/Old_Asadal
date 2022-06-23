// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdKRGDialogueNode.h"

#include "EdKRGDialogueNode_Branch.generated.h"

/**
 * 
 */
UCLASS()
class KRGDIALOGUEEDITOR_API UEdKRGDialogueNode_Branch : public UEdKRGDialogueNode
{
	GENERATED_BODY()
	
protected:
	virtual void AllocateDefaultPins() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
};
