// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element/KRGDialogueElement.h"
#include "EdKRGDialogueElement.generated.h"

/**
 * 
 */
 
UCLASS(Abstract)
class KRGDIALOGUEEDITOR_API UEdKRGDialogueElement : public UEdGraphNode
{
	GENERATED_BODY()

public :
	virtual void SetTemplateFlag(EObjectFlags NewFlags);
	virtual void SetGraphElement(UObject* Outer, TSubclassOf<UKRGDialogueElement> GraphElementClass);
	virtual UKRGDialogueElement* GetGraphElement() const;
	virtual bool CanUserDeleteNode() const override;

protected:
	UPROPERTY()
	UKRGDialogueElement* GraphElement;
};
