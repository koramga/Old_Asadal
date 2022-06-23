// Fill out your copyright notice in the Description page of Project Settings.


#include "Element/Node/KRGDialogueNode.h"

#define LOCTEXT_NAMESPACE "KRGDialogueNode"

UKRGDialogueNode::UKRGDialogueNode()
{
}

UKRGDialogueNode::~UKRGDialogueNode()
{
}

TArray<UKRGDialogueNode*>& UKRGDialogueNode::GetChildrenNodes()
{
	return ChildrenNodes;
}

TArray<UKRGDialogueNode*>& UKRGDialogueNode::GetParentNodes()
{
	return ParentNodes;
}

void UKRGDialogueNode::Clear()
{
	ParentNodes.Empty();
	ChildrenNodes.Empty();
	Edges.Empty();
}

void UKRGDialogueNode::AddChildNode(UKRGDialogueNode* ChildNode)
{
	ChildrenNodes.Add(ChildNode);
}

void UKRGDialogueNode::RemoveChildNode(UKRGDialogueNode* ChildNode)
{
	ChildrenNodes.Remove(ChildNode);
}

void UKRGDialogueNode::ClearChildNodes()
{
	ChildrenNodes.Reset();
}

bool UKRGDialogueNode::IsEmptyChildNode() const
{
	if (ParentNodes.Num() == 0)
	{
		return true;
	}

	return false;
}

void UKRGDialogueNode::AddParentNode(UKRGDialogueNode* ParentNode)
{
	ParentNodes.Add(ParentNode);
}

void UKRGDialogueNode::RemoveParentNode(UKRGDialogueNode* ParentNode)
{
	ParentNodes.Remove(ParentNode);
}

void UKRGDialogueNode::ClearParentNodes()
{
	ParentNodes.Reset();
}

bool UKRGDialogueNode::IsEmptyParentNode() const
{
	if (ParentNodes.Num() == 0)
	{
		return true;
	}

	return false;
}

void UKRGDialogueNode::AddEdge(UKRGDialogueNode* InNode, UKRGDialogueEdge* InEdge)
{
	Edges.Add(InNode, InEdge);
}

void UKRGDialogueNode::ClearEdges()
{
	Edges.Reset();
}

bool UKRGDialogueNode::CanUserDeleteNode()
{
	return true;
}

UKRGDialogueEdge* UKRGDialogueNode::GetEdge(UKRGDialogueNode* ChildNode)
{
	return Edges.Contains(ChildNode) ? Edges.FindChecked(ChildNode) : nullptr;
}

bool UKRGDialogueNode::IsLeafNode() const
{
	return ChildrenNodes.Num() == 0;
}

bool UKRGDialogueNode::IsRootNode() const
{
	return ParentNodes.Num() == 0;
}

FText UKRGDialogueNode::GetDescription_Implementation() const
{
	return LOCTEXT("NodeDesc", "Script Graph Node");
}

#if WITH_EDITOR
bool UKRGDialogueNode::IsNameEditable() const
{
	return true;
}

FLinearColor UKRGDialogueNode::GetBackgroundColor() const
{
	return BackgroundColor;
}

FText UKRGDialogueNode::GetNodeTitle() const
{
	return NodeTitle.IsEmpty() ? GetDescription() : NodeTitle;
}

FText UKRGDialogueNode::GetContextMenuName() const
{
	return ContextMenuName;
}

const TSubclassOf<UKRGDialogueNode>& UKRGDialogueNode::GetCompatibleGraphType() const
{
	return CompatibleGraphType;
}

void UKRGDialogueNode::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}

bool UKRGDialogueNode::CanCreateConnection(UKRGDialogueNode* Other, FText& ErrorMessage)
{
	return true;
}

bool UKRGDialogueNode::CanCreateConnectionTo(UKRGDialogueNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage)
{
	//if( ENodeLimit::Limited == ChildrenLimitType
	//	&& NumberOfChildrenNodes >= ChildrenLimit)
	//{
	//	ErrorMessage = FText::FromString("Children limit exceeded");
	//	return false;
	//}

	return CanCreateConnection(Other, ErrorMessage);
}

bool UKRGDialogueNode::CanCreateConnectionFrom(UKRGDialogueNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage)
{
	//if(ENodeLimit::Limited == ParentLimitType
	//	&& NumberOfParentNodes >= ParentLimit)
	//{
	//	ErrorMessage = FText::FromString("Parent limit exceeded");
	//	return false;
	//}

	return true;
}
#endif

#undef LOCTEXT_NAMESPACE
