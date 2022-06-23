#pragma once
#include "ConnectionDrawingPolicy.h"

class FConnectionDrawingPolicy_KRGDialogueBase : public FConnectionDrawingPolicy
{
public :
	FConnectionDrawingPolicy_KRGDialogueBase(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InEdGraph);
	
protected:
	UEdGraph* EdGraph;
	TMap<UEdGraphNode*, int32> NodeWidgetMap;
};
