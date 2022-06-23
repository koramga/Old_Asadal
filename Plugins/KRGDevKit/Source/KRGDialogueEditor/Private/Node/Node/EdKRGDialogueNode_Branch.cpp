// Fill out your copyright notice in the Description page of Project Settings.


#include "EdKRGDialogueNode_Branch.h"

void UEdKRGDialogueNode_Branch::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "WorkNode", FName(), TEXT("Work"));
	CreatePin(EGPD_Output, "TrueNode", FName(), TEXT("True"));
	CreatePin(EGPD_Output, "FalseNode", FName(), TEXT("False"));
}

void UEdKRGDialogueNode_Branch::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}
