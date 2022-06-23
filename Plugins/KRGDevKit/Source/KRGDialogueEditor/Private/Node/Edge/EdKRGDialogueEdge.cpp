// Fill out your copyright notice in the Description page of Project Settings.


#include "EdKRGDialogueEdge.h"
#include "Element/Edge/KRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode.h"

UEdKRGDialogueEdge::UEdKRGDialogueEdge()
{
	bCanRenameNode = true;
}

void UEdKRGDialogueEdge::SetEdge(UKRGDialogueEdge* InEdge)
{
	GraphElement = InEdge;
}

void UEdKRGDialogueEdge::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, TEXT("Edge"), FName(), TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, TEXT("Edge"), FName(), TEXT("Out"));
	Outputs->bHidden = true;
}

FText UEdKRGDialogueEdge::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	UKRGDialogueEdge* Edge = GetEdge();
	
	if(IsValid(Edge))
	{
		return Edge->GetNodeTitle();
	}

	return FText();
}

void UEdKRGDialogueEdge::PinConnectionListChanged(UEdGraphPin* Pin)
{
	if(Pin->LinkedTo.Num() == 0)
	{
		//Commit suicide; transitions must always have an input and output connection
		Modify();

		//Our parent graph will have our graph in SubGraphs so needs to be modified to record that.
		if(UEdGraph* ParentGraph = GetGraph())
		{
			ParentGraph->Modify();
		}

		DestroyNode();
	}
}

void UEdKRGDialogueEdge::PrepareForCopying()
{
	UKRGDialogueEdge* Edge = GetEdge();
	
	if(IsValid(Edge))
	{
		Edge->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	}	
}

void UEdKRGDialogueEdge::CreateConnections(UEdKRGDialogueNode* Start, UEdKRGDialogueNode* End)
{
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	Start->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(Start->GetOutputPin());

	//This to text
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	End->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(End->GetInputPin());
}

UEdKRGDialogueNode* UEdKRGDialogueEdge::GetEdStartNode() const
{
	if(Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UEdKRGDialogueNode>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UEdKRGDialogueNode* UEdKRGDialogueEdge::GetEdEndNode() const
{
	if(Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UEdKRGDialogueNode>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return nullptr;
	}
}

UKRGDialogueEdge* UEdKRGDialogueEdge::GetEdge() const
{
	return Cast<UKRGDialogueEdge>(GraphElement);
}

void UEdKRGDialogueEdge::SetTemplateFlag(EObjectFlags NewFlags)
{
	Super::SetTemplateFlag(NewFlags);

	UKRGDialogueEdge* Edge = GetEdge();

	if(IsValid(Edge))
	{
		Edge->SetFlags(NewFlags);
	}
}
