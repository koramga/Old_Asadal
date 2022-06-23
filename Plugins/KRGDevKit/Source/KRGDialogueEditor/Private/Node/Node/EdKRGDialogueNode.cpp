// Fill out your copyright notice in the Description page of Project Settings.


#include "EdKRGDialogueNode.h"

#include "Graph/EdKRGDialogueGraph.h"


UEdKRGDialogueNode::UEdKRGDialogueNode()
{
	bCanRenameNode = true;
}

UEdKRGDialogueNode::~UEdKRGDialogueNode()
{
}

UKRGDialogueNode* UEdKRGDialogueNode::GetNode() const
{
	return Cast<UKRGDialogueNode>(GraphElement);
}

void UEdKRGDialogueNode::SetNode(UKRGDialogueNode* InNode)
{
	GraphElement = InNode;
}

void UEdKRGDialogueNode::SetSEdNode(SEdKRGDialogueNode* InSEdNode)
{
	SEdNode = InSEdNode;
}

UEdKRGDialogueGraph* UEdKRGDialogueNode::GetEdGraph()
{
	return Cast<UEdKRGDialogueGraph>(GetGraph());
}

void UEdKRGDialogueNode::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, "MultipleNodes", FName(), TEXT("In"));
	CreatePin(EGPD_Output, "MultipleNodes", FName(), TEXT("Out"));
}

FText UEdKRGDialogueNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UKRGDialogueNode* Node = GetNode();
	if(IsValid(Node))
	{
		return Node->GetNodeTitle();
	}
	else
	{
		return Super::GetNodeTitle(TitleType);
	}	
}

void UEdKRGDialogueNode::PrepareForCopying()
{
	UKRGDialogueNode* Node = GetNode();

	if(IsValid(Node))
	{
		Node->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	}	
}

void UEdKRGDialogueNode::AutowireNewNode(UEdGraphPin* FromPin)
{
	Super::AutowireNewNode(FromPin);

	if(FromPin != nullptr)
	{
		if(GetSchema()->TryCreateConnection(FromPin, GetInputPin()))
		{
			FromPin->GetOwningNode()->NodeConnectionListChanged();
		}
	}
}

bool UEdKRGDialogueNode::CanUserDeleteNode() const
{
	UKRGDialogueNode* BaseNode = GetNode();

	return BaseNode->CanUserDeleteNode();
}

FLinearColor UEdKRGDialogueNode::GetBackgroundColor() const
{
	UKRGDialogueNode* Node = GetNode();
	
	return IsValid(Node) ? Node->GetBackgroundColor() : FLinearColor::Black;
}

UEdGraphPin* UEdKRGDialogueNode::GetInputPin() const
{
	return Pins[0];
}

UEdGraphPin* UEdKRGDialogueNode::GetOutputPin() const
{
	return Pins[1];
}

#if WITH_EDITOR
void UEdKRGDialogueNode::PostEditUndo()
{
	Super::PostEditUndo();
}
#endif
