#include "ConnectionDrawingPolicy_KRGDialogueStraight.h"
#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode.h"

ConnectionDrawingPolicy_KRGDialogueStraight::ConnectionDrawingPolicy_KRGDialogueStraight(int32 InBackLayerID, int32 InFrontLayerID,
                                                                                         float ZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements, UEdGraph* InEdGraph)
		: ::FConnectionDrawingPolicy_KRGDialogueBase(InBackLayerID, InFrontLayerID, ZoomFactor, InClippingRect, InDrawElements, InEdGraph)
{
}

void ConnectionDrawingPolicy_KRGDialogueStraight::DetermineWiringStyle(UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
	FConnectionParams& Params)
{	
	Params.AssociatedPin1 = OutputPin;
	Params.AssociatedPin2 = InputPin;
	Params.WireThickness = 1.5f;
	
	const bool bDeemphasizeUnhoveredPins = HoveredPins.Num() > 0;
	if(bDeemphasizeUnhoveredPins)
	{
		ApplyHoverDeemphasis(OutputPin, InputPin, Params.WireThickness, Params.WireColor);
	}
}

void ConnectionDrawingPolicy_KRGDialogueStraight::Draw(TMap<TSharedRef<SWidget>, FArrangedWidget>& InPinGeometries,
	FArrangedChildren& ArrangedNodes)
{
	NodeWidgetMap.Empty();

	for(int32 NodeIndex = 0; NodeIndex < ArrangedNodes.Num(); ++NodeIndex)
	{
		FArrangedWidget& CurWidget = ArrangedNodes[NodeIndex];
		TSharedRef<SGraphNode> ChildNode = StaticCastSharedRef<SGraphNode>(CurWidget.Widget);
		NodeWidgetMap.Add(ChildNode->GetNodeObj(), NodeIndex);
	}

	//Now draw.
	FConnectionDrawingPolicy_KRGDialogueBase::Draw(InPinGeometries, ArrangedNodes);
}

void ConnectionDrawingPolicy_KRGDialogueStraight::DrawSplineWithArrow(const FGeometry& StartGeom, const FGeometry& EndGeom,
	const FConnectionParams& Params)
{
	//Build an acceleration structure to quickly find geometry for the nodes.
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	//Find the (approximate) closet points between the two boxes.
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

	DrawSplineWithArrow(StartAnchorPoint, EndAnchorPoint, Params);
}

void ConnectionDrawingPolicy_KRGDialogueStraight::DrawSplineWithArrow(const FVector2D& StartPoint, const FVector2D& EndPoint,
	const FConnectionParams& Params)
{
	// bUserFlag1 indicates that we need to reverse the direction of connection (used by debugger)
	const FVector2D& P0 = Params.bUserFlag1 ? EndPoint : StartPoint;
	const FVector2D& P1 = Params.bUserFlag1 ? StartPoint : EndPoint;

	Internal_DrawLineWithArrow(P0, P1, Params);
}

void ConnectionDrawingPolicy_KRGDialogueStraight::DrawPreviewConnector(const FGeometry& PinGeometry,
	const FVector2D& StartPoint, const FVector2D& EndPoint, UEdGraphPin* Pin)
{
	FConnectionParams Params;
	DetermineWiringStyle(Pin, nullptr, /*inout*/ Params);

	if (Pin->Direction == EEdGraphPinDirection::EGPD_Output)
	{
		DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, EndPoint), EndPoint, Params);
	}
	else
	{
		DrawSplineWithArrow(FGeometryHelper::FindClosestPointOnGeom(PinGeometry, StartPoint), StartPoint, Params);
	}
}

FVector2D ConnectionDrawingPolicy_KRGDialogueStraight::ComputeSplineTangent(const FVector2D& Start, const FVector2D& End) const
{
	const FVector2D Delta = End - Start;
	const FVector2D NormDelta = Delta.GetSafeNormal();

	return NormDelta;
}

void ConnectionDrawingPolicy_KRGDialogueStraight::DetermineLinkGeometry(FArrangedChildren& ArrangedNodes,
	TSharedRef<SWidget>& OutputPinWidget, UEdGraphPin* OutputPin, UEdGraphPin* InputPin,
	FArrangedWidget*& StartWidgetGeometry, FArrangedWidget*& EndWidgetGeometry)
{
	if (UEdKRGDialogueEdge* EdgeNode = Cast<UEdKRGDialogueEdge>(InputPin->GetOwningNode()))
	{
		UEdKRGDialogueNode* Start = EdgeNode->GetEdStartNode();
		UEdKRGDialogueNode* End = EdgeNode->GetEdEndNode();
		if (Start != nullptr && End != nullptr)
		{
			int32* StartNodeIndex = NodeWidgetMap.Find(Start);
			int32* EndNodeIndex = NodeWidgetMap.Find(End);
			if (StartNodeIndex != nullptr && EndNodeIndex != nullptr)
			{
				StartWidgetGeometry = &(ArrangedNodes[*StartNodeIndex]);
				EndWidgetGeometry = &(ArrangedNodes[*EndNodeIndex]);
			}
		}
	}
	else
	{
		StartWidgetGeometry = PinGeometries->Find(OutputPinWidget);

		if (TSharedPtr<SGraphPin>* pTargetWidget = PinToPinWidgetMap.Find(InputPin))
		{
			TSharedRef<SGraphPin> InputWidget = (*pTargetWidget).ToSharedRef();
			EndWidgetGeometry = PinGeometries->Find(InputWidget);
		}
	}
}

void ConnectionDrawingPolicy_KRGDialogueStraight::Internal_DrawLineWithArrow(const FVector2D& StartAnchorPoint,
	const FVector2D& EndAnchorPoint, const FConnectionParams& Params)
{
	//@TODO: Should this be scaled by zoom factor?
	const float LineSeparationAmount = 4.5f;

	const FVector2D DeltaPos = EndAnchorPoint - StartAnchorPoint;
	const FVector2D UnitDelta = DeltaPos.GetSafeNormal();
	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	// Come up with the final start/end points
	const FVector2D DirectionBias = Normal * LineSeparationAmount;
	const FVector2D LengthBias = ArrowRadius.X * UnitDelta;
	const FVector2D StartPoint = StartAnchorPoint + DirectionBias + LengthBias;
	const FVector2D EndPoint = EndAnchorPoint + DirectionBias - LengthBias;

	// Draw a line/spline
	DrawConnection(WireLayerID, StartPoint, EndPoint, Params);

	// Draw the arrow
	const FVector2D ArrowDrawPos = EndPoint - ArrowRadius;
	const float AngleInRadians = FMath::Atan2(DeltaPos.Y, DeltaPos.X);

	FSlateDrawElement::MakeRotatedBox(
		DrawElementsList,
		ArrowLayerID,
		FPaintGeometry(ArrowDrawPos, ArrowImage->ImageSize * ZoomFactor, ZoomFactor),
		ArrowImage,
		ESlateDrawEffect::None,
		AngleInRadians,
		TOptional<FVector2D>(),
		FSlateDrawElement::RelativeToElement,
		Params.WireColor
	);
}
