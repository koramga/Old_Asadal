// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEdKRGDialogueNode.h"
#include "SGraphPin.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class KRGDIALOGUEEDITOR_API SEdKRGDialogueNode_Script : public SEdKRGDialogueNode
{
public:
	SLATE_BEGIN_ARGS(SEdKRGDialogueNode_Script){}
		SLATE_ARGUMENT(UEdGraphNode*, EdGraphNode)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
};
