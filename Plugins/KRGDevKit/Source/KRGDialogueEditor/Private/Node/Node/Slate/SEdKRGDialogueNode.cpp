// Fill out your copyright notice in the Description page of Project Settings.


#include "SEdKRGDialogueNode.h"
#include "SlateOptMacros.h"
#include "Graph/EdKRGDialogueGraph.h"
#include "Node/Node/EdKRGDialogueNode.h"
#include "Utility/EdKRGDialogueColor.h"
#include "Graph/KRGDialogueGraph.h"

bool SEdKRGDialogueNode::IsNameReadOnly() const
{
	UEdKRGDialogueNode* EdNode = Cast<UEdKRGDialogueNode>(GraphNode);
	check(nullptr != EdNode);

	UKRGDialogueGraph* Graph = EdNode->GetNode()->GetGraph();
	check(Graph != nullptr);

	return (!Graph->bCanRenameNode || !EdNode->GetNode()->IsNameEditable()) || SGraphNode::IsNameReadOnly();
}

void SEdKRGDialogueNode::Construct(const FArguments& InArgs)
{
	GraphNode = InArgs._EdGraphNode;

	InitializeNode();
}

void SEdKRGDialogueNode::InitializeNode()
{
	UEdKRGDialogueNode* BaseNode = Cast<UEdKRGDialogueNode>(GraphNode);

	if(IsValid(BaseNode))
	{
		BaseNode->SetSEdNode(this);
	}

	UpdateGraphNode();
}

FSlateColor SEdKRGDialogueNode::GetBorderBackgroundColor() const
{
	UEdKRGDialogueNode* Node = CastChecked<UEdKRGDialogueNode>(GraphNode);
	return Node ? Node->GetBackgroundColor() : EdKRGDialogueColor::NodeBorder::HighlightAbortRange0;
}

FSlateColor SEdKRGDialogueNode::GetBackgroundColor() const
{
	return EdKRGDialogueColor::NodeBody::Default;
}

EVisibility SEdKRGDialogueNode::GetDragOverMarkerVisibility() const
{
	return EVisibility::Visible;
}

const FSlateBrush* SEdKRGDialogueNode::GetNameIcon() const
{
	return FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon"));
}

void SEdKRGDialogueNode::OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo)
{
	SEdKRGDialogueElement::OnNameTextCommited(InText, CommitInfo);

	UEdKRGDialogueNode* MyNode = CastChecked<UEdKRGDialogueNode>(GraphNode);

	if(MyNode != nullptr && MyNode->GetNode() != nullptr)
	{
		const FScopedTransaction Transaction(FText::FromString(TEXT("Rename Node")));
		MyNode->Modify();
		MyNode->GetNode()->Modify();
		MyNode->GetNode()->SetNodeTitle(InText);
		UpdateGraphNode();
	}	
}
