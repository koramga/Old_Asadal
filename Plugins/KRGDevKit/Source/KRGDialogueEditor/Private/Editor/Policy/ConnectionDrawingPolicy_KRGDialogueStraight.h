#pragma once
#include "ConnectionDrawingPolicy_KRGDialogueBase.h"

class ConnectionDrawingPolicy_KRGDialogueStraight : public FConnectionDrawingPolicy_KRGDialogueBase
{
public:
	ConnectionDrawingPolicy_KRGDialogueStraight(int32 InBackLayerID, int32 InFrontLayerID, float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InEdGraph);

	//FCoonnectionDrawingPolicy Interface
	virtual void DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FConnectionParams& Params) override;
	virtual void Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries, FArrangedChildren& ArrangedNodes) override;
	virtual void DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom, const FConnectionParams& Params) override;
	virtual void DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint, const FConnectionParams& Params) override;
	virtual void DrawPreviewConnector(const FGeometry& PinGeometry, const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin) override;
	virtual FVector2D ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const override;
	virtual void DetermineLinkGeometry(FArrangedChildren& ArrangedNodes, TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin, FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry) override;
	//End of FConnectionDrawingPolicy interface
	
	protected:
	void Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint, const FVector2D& EndAnchorPoint, const FConnectionParams& Params);	
};
