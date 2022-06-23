// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/SEdKRGDialogueElement.h"


/**
 * 
 */
class KRGDIALOGUEEDITOR_API SEdKRGDialogueNode : public SEdKRGDialogueElement
{
public :
	SLATE_BEGIN_ARGS(SEdKRGDialogueNode) {}
		SLATE_ARGUMENT(UEdGraphNode*, EdGraphNode)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	virtual void InitializeNode();

	virtual FSlateColor GetBorderBackgroundColor() const;
	virtual FSlateColor GetBackgroundColor() const;

	virtual EVisibility GetDragOverMarkerVisibility() const;

	virtual const FSlateBrush* GetNameIcon() const;

	virtual void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);
	virtual bool IsNameReadOnly() const override;
};
