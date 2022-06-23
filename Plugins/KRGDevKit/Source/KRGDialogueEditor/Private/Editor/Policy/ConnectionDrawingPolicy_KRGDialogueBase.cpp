#include "ConnectionDrawingPolicy_KRGDialogueBase.h"

FConnectionDrawingPolicy_KRGDialogueBase::FConnectionDrawingPolicy_KRGDialogueBase(int32 InBackLayerID, int32 InFrontLayerID,
	float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InEdGraph)
		: FConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements)
		, EdGraph(InEdGraph)
{
}
