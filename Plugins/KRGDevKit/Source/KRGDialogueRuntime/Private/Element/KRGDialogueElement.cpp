// Fill out your copyright notice in the Description page of Project Settings.


#include "Element/KRGDialogueElement.h"
#include "Graph/KRGDialogueGraph.h"

UKRGDialogueElement::UKRGDialogueElement()
{
}

UKRGDialogueElement::~UKRGDialogueElement()
{
}

void UKRGDialogueElement::SetGraph(UKRGDialogueGraph* InGraph)
{
	Graph = InGraph;
}

UKRGDialogueGraph* UKRGDialogueElement::GetGraph() const
{
	return Graph;
}
