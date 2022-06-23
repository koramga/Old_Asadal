// Fill out your copyright notice in the Description page of Project Settings.


#include "EdKRGDialogueElement.h"

void UEdKRGDialogueElement::SetTemplateFlag(EObjectFlags NewFlags)
{
	GraphElement->SetFlags(NewFlags);
}

void UEdKRGDialogueElement::SetGraphElement(UObject* Outer, TSubclassOf<UKRGDialogueElement> GraphElementClass)
{
	GraphElement = NewObject<UKRGDialogueElement>(Outer, GraphElementClass);
}

UKRGDialogueElement* UEdKRGDialogueElement::GetGraphElement() const
{
	return GraphElement;
}

bool UEdKRGDialogueElement::CanUserDeleteNode() const
{
	return false;
}
