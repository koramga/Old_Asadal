// Fill out your copyright notice in the Description page of Project Settings.


#include "SEdGraphPin_KRGDialogue.h"

#include "SlateOptMacros.h"
#include "Editor/Action/KRGDialogueGraphDragConnection.h"
#include "Utility/EdKRGDialogueColor.h"


BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdGraphPin_KRGDialogue::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	this->SetCursor(EMouseCursor::Default);

	bShowLabel = true;

	GraphPinObj = InPin;
	check(GraphPinObj != nullptr);

	const UEdGraphSchema* Schema = GraphPinObj->GetSchema();
	check(Schema);

	SBorder::Construct(SBorder::FArguments()
		.BorderImage(this, &SEdGraphPin_KRGDialogue::GetPinBorder)
		.BorderBackgroundColor(this, &SEdGraphPin_KRGDialogue::GetPinColor)
		.OnMouseButtonDown(this, &SEdGraphPin_KRGDialogue::OnPinMouseDown)
		.Cursor(this, &SEdGraphPin_KRGDialogue::GetPinCursor)
		.Padding(FMargin(5.f))
	);
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

FSlateColor SEdGraphPin_KRGDialogue::GetPinColor() const
{
	return EdKRGDialogueColor::Pin::Default;
}

TSharedRef<SWidget> SEdGraphPin_KRGDialogue::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}

TSharedRef<FDragDropOperation> SEdGraphPin_KRGDialogue::SpawnPinDragEvent(const TSharedRef<SGraphPanel>& InGraphPanel,
	const TArray<TSharedRef<SGraphPin>>& InStartingPins)
{
	FKRGDialogueGraphDragConnection::FDraggedPinTable PinHandles;
	PinHandles.Reserve(InStartingPins.Num());

	for(const TSharedRef<SGraphPin>& PinWidget : InStartingPins)
	{
		PinHandles.Add(PinWidget->GetPinObj());
	}

	return FKRGDialogueGraphDragConnection::New(InGraphPanel, PinHandles);
}

const FSlateBrush* SEdGraphPin_KRGDialogue::GetPinBorder() const
{
	return FAppStyle::GetBrush(TEXT("Graph.StateNode.Body"));
}
