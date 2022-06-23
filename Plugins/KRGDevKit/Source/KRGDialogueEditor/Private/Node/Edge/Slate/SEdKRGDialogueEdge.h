// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/SEdKRGDialogueElement.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class KRGDIALOGUEEDITOR_API SEdKRGDialogueEdge : public SEdKRGDialogueElement
{
public:
	SLATE_BEGIN_ARGS(SEdKRGDialogueEdge)	{}
	SLATE_ARGUMENT(UEdGraphNode*, EdGraphNode)
SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

	virtual bool RequiresSecondPassLayout() const override;
	virtual void PerformSecondPassLayout(const TMap<UObject*, TSharedRef<SNode>>& InNodeToWidgetLookup) const override;
	virtual void UpdateGraphNode() override;

	//Calculate position for multiple nodes to be placed between a start and end point, by providing this nodes index and max expected nodes
	void PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom, int32 NodeIndex, int32 MaxNodes) const;
	void OnNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo);

protected:
	FSlateColor GetEdgeColor() const;
	const FSlateBrush* GetEdgeImage() const;
	EVisibility GetEdgeImageVisibility() const;
	EVisibility GetEdgeTitleVisibility() const;

private:
	TSharedPtr<STextEntryPopup> TextEntryWidget;
	
};
