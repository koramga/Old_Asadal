// Fill out your copyright notice in the Description page of Project Settings.


#include "Element/Edge/KRGDialogueEdge.h"

UKRGDialogueEdge::UKRGDialogueEdge()
{
}

UKRGDialogueEdge::~UKRGDialogueEdge()
{
}

UKRGDialogueNode* UKRGDialogueEdge::GetStartNode() const
{
	return StartNode;
}

UKRGDialogueNode* UKRGDialogueEdge::GetEndNode() const
{
	return EndNode;
}

void UKRGDialogueEdge::SetStartNode(UKRGDialogueNode* InStartNode)
{
	StartNode = InStartNode;
}

void UKRGDialogueEdge::SetEndNode(UKRGDialogueNode* InEndNode)
{
	EndNode = InEndNode;
}

#if WITH_EDITOR
void UKRGDialogueEdge::SetNodeTitle(const FText& NewTitle)
{
	NodeTitle = NewTitle;
}
#endif

