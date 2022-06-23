#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"

class KRGDIALOGUEEDITOR_API SEdKRGDialogueElement : public SGraphNode
{
public:
	SLATE_BEGIN_ARGS(SEdKRGDialogueElement){}
		SLATE_ARGUMENT(UEdGraphNode*, EdGraphNode)
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	/*
		virtual void UpdateGraphNode() override;
		virtual void CreatePinWidgets() override;
		virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
		virtual bool IsNameReadOnly() const override;
	
		void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInformation);	
	
		virtual FSlateColor GetBorderBackgroundColor() const;
		virtual FSlateColor GetBackgroundColor() const;
	
		virtual EVisibility GetDragOverMarkerVisibility() const;
		virtual FSlateBrush* GetNameIcon() const;
	*/

protected:
	UEdGraphNode*	EdGraphNode;
};
