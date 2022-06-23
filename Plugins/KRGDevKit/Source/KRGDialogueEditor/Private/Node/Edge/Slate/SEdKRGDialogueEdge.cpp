// Fill out your copyright notice in the Description page of Project Settings.


#include "SEdKRGDialogueEdge.h"

#include "ConnectionDrawingPolicy.h"
#include "SlateOptMacros.h"
#include "Element/Edge/KRGDialogueEdge.h"
#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"

void SEdKRGDialogueEdge::Construct(const FArguments& InArgs)
{
	GraphNode = InArgs._EdGraphNode;
	UpdateGraphNode();	
}

bool SEdKRGDialogueEdge::RequiresSecondPassLayout() const
{
	return true;
}

void SEdKRGDialogueEdge::PerformSecondPassLayout(
	const TMap<UObject*, TSharedRef<SNode>>& InNodeToWidgetLookup) const
{
	UEdKRGDialogueEdge* EdgeNode = CastChecked<UEdKRGDialogueEdge>(GraphNode);

	FGeometry StartGeom;
	FGeometry EndGeom;

	UEdKRGDialogueNode* Start = EdgeNode->GetEdStartNode();
	UEdKRGDialogueNode* End = EdgeNode->GetEdEndNode();
	if (Start != nullptr && End != nullptr)
	{
		const TSharedRef<SNode>* pFromWidget = InNodeToWidgetLookup.Find(Start);
		const TSharedRef<SNode>* pToWidget = InNodeToWidgetLookup.Find(End);
		if (pFromWidget != nullptr && pToWidget != nullptr)
		{
			const TSharedRef<SNode>& FromWidget = *pFromWidget;
			const TSharedRef<SNode>& ToWidget = *pToWidget;

			StartGeom = FGeometry(FVector2D(Start->NodePosX, Start->NodePosY), FVector2D::ZeroVector, FromWidget->GetDesiredSize(), 1.0f);
			EndGeom = FGeometry(FVector2D(End->NodePosX, End->NodePosY), FVector2D::ZeroVector, ToWidget->GetDesiredSize(), 1.0f);
		}
	}

	PositionBetweenTwoNodesWithOffset(StartGeom, EndGeom, 0, 1);
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEdKRGDialogueEdge::UpdateGraphNode()
{
	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind( this, &SGraphNode::GetContentScale );
	this->GetOrAddSlot( ENodeZone::Center )
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(FEditorStyle::GetBrush("Graph.TransitionNode.ColorSpill"))
				.ColorAndOpacity(this, &SEdKRGDialogueEdge::GetEdgeColor)
			]
			+ SOverlay::Slot()
			[
				SNew(SImage)
				.Image(this, &SEdKRGDialogueEdge::GetEdgeImage)
				.Visibility(this, &SEdKRGDialogueEdge::GetEdgeImageVisibility)
			]

			+ SOverlay::Slot()
			.Padding(FMargin(4.0f, 4.0f, 4.0f, 4.0f))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot()
				.HAlign(HAlign_Center)
				.AutoHeight()
				[
					SAssignNew(InlineEditableText, SInlineEditableTextBlock)
					.ColorAndOpacity(FLinearColor::Black)
					.Visibility(this, &SEdKRGDialogueEdge::GetEdgeTitleVisibility)
					.Font(FCoreStyle::GetDefaultFontStyle("Regular", 12))
					.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
					.OnTextCommitted(this, &SEdKRGDialogueEdge::OnNameTextCommited)
				]
				+ SVerticalBox::Slot()
				.AutoHeight()
				[
					NodeTitle.ToSharedRef()
				]
				
			]
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdKRGDialogueEdge::PositionBetweenTwoNodesWithOffset(const FGeometry& StartGeom, const FGeometry& EndGeom,
	int32 NodeIndex, int32 MaxNodes) const
{
	// Get a reasonable seed point (halfway between the boxes)
	const FVector2D StartCenter = FGeometryHelper::CenterOf(StartGeom);
	const FVector2D EndCenter = FGeometryHelper::CenterOf(EndGeom);
	const FVector2D SeedPoint = (StartCenter + EndCenter) * 0.5f;

	// Find the (approximate) closest points between the two boxes
	const FVector2D StartAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(StartGeom, SeedPoint);
	const FVector2D EndAnchorPoint = FGeometryHelper::FindClosestPointOnGeom(EndGeom, SeedPoint);

	// Position ourselves halfway along the connecting line between the nodes, elevated away perpendicular to the direction of the line
	const float Height = 30.0f;

	const FVector2D DesiredNodeSize = GetDesiredSize();

	FVector2D DeltaPos(EndAnchorPoint - StartAnchorPoint);

	if (DeltaPos.IsNearlyZero())
	{
		DeltaPos = FVector2D(10.0f, 0.0f);
	}

	const FVector2D Normal = FVector2D(DeltaPos.Y, -DeltaPos.X).GetSafeNormal();

	const FVector2D NewCenter = StartAnchorPoint + (0.5f * DeltaPos) + (Height * Normal);

	FVector2D DeltaNormal = DeltaPos.GetSafeNormal();
	
	// Calculate node offset in the case of multiple transitions between the same two nodes
	// MultiNodeOffset: the offset where 0 is the centre of the transition, -1 is 1 <size of node>
	// towards the PrevStateNode and +1 is 1 <size of node> towards the NextStateNode.

	const float MutliNodeSpace = 0.2f; // Space between multiple transition nodes (in units of <size of node> )
	const float MultiNodeStep = (1.f + MutliNodeSpace); //Step between node centres (Size of node + size of node spacer)

	const float MultiNodeStart = -((MaxNodes - 1) * MultiNodeStep) / 2.f;
	const float MultiNodeOffset = MultiNodeStart + (NodeIndex * MultiNodeStep);

	// Now we need to adjust the new center by the node size, zoom factor and multi node offset
	const FVector2D NewCorner = NewCenter - (0.5f * DesiredNodeSize) + (DeltaNormal * MultiNodeOffset * DesiredNodeSize.Size());

	GraphNode->NodePosX = NewCorner.X;
	GraphNode->NodePosY = NewCorner.Y;
}

void SEdKRGDialogueEdge::OnNameTextCommitted(const FText& InText, ETextCommit::Type CommitInfo)
{
	SEdKRGDialogueElement::OnNameTextCommited(InText, CommitInfo);

	UEdKRGDialogueEdge* EdEdge = CastChecked<UEdKRGDialogueEdge>(GraphNode);

	if(EdEdge != nullptr && EdEdge->GetEdge() != nullptr)
	{
		const FScopedTransaction Transaction(FText::FromString(TEXT("Rename Edge")));
		EdEdge->Modify();
		EdEdge->GetEdge()->SetNodeTitle(InText);
		UpdateGraphNode();
	}
}

FSlateColor SEdKRGDialogueEdge::GetEdgeColor() const
{
	UEdKRGDialogueEdge* EdEdge = CastChecked<UEdKRGDialogueEdge>(GraphNode);

	if(EdEdge != nullptr && EdEdge->GetEdge() != nullptr)
	{
		return EdEdge->GetEdge()->GetEdgeColor();
	}

	return FLinearColor(0.9f, 0.9f, 0.9f, 1.f);
}

const FSlateBrush* SEdKRGDialogueEdge::GetEdgeImage() const
{
	return FEditorStyle::GetBrush( TEXT("Graph.TransitionNode.Icon"));
}

EVisibility SEdKRGDialogueEdge::GetEdgeImageVisibility() const
{
	UEdKRGDialogueEdge* EdEdge = CastChecked<UEdKRGDialogueEdge>(GraphNode);
	if(EdEdge && EdEdge->GetEdge() && EdEdge->GetEdge()->bShouldDrawTitle)
	{
		return EVisibility::Hidden;
	}

	return EVisibility::Visible;
}

EVisibility SEdKRGDialogueEdge::GetEdgeTitleVisibility() const
{
	UEdKRGDialogueEdge* EdEdge = CastChecked<UEdKRGDialogueEdge>(GraphNode);
	if(EdEdge && EdEdge->GetEdge() && EdEdge->GetEdge()->bShouldDrawTitle)
	{
		return EVisibility::Visible;
	}

	return EVisibility::Collapsed;
}
