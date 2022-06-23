// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SEdKRGDialogueNode.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class KRGDIALOGUEEDITOR_API SEdKRGDialogueNode_Branch : public SEdKRGDialogueNode
{
public:
	SLATE_BEGIN_ARGS(SEdKRGDialogueNode_Branch){}
		SLATE_ARGUMENT(UEdGraphNode*, EdGraphNode)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void UpdateGraphNode() override;

protected:
	virtual void SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget) override;
};
