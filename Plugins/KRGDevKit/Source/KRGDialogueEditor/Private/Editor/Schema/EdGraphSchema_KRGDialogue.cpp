// Fill out your copyright notice in the Description page of Project Settings.


#include "EdGraphSchema_KRGDialogue.h"

#include "GraphEditorActions.h"
#include "ToolMenuSection.h"
#include "Editor/Action/EdGraphSchemaAction_KRGDialogueNew.h"
#include "Editor/Policy/ConnectionDrawingPolicy_KRGDialogueBase.h"
#include "Graph/KRGDialogueGraph.h"
#include "Framework/Commands/GenericCommands.h"
#include "Graph/EdKRGDialogueGraph.h"
#include "ToolMenu.h"
#include "Element/Node/KRGDialogueNode_Branch.h"
#include "Element/Node/KRGDialogueNode_Script.h"
#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode_Branch.h"
#include "Node/Node/EdKRGDialogueNode_Script.h"

int32 UEdGraphSchema_KRGDialogue::CurrentCacheRefreshID = 0;

class FNodeVisitorCyclceChecker
{
public :
	bool CheckForLoop(UEdGraphNode* StartNode, UEdGraphNode* EndNode)
	{
		VisitedNodes.Add(StartNode);

	return TraverseNodes(EndNode);
	}

private:
	bool TraverseNodes(UEdGraphNode* Node)
	{
		VisitedNodes.Add(Node);

		for(auto MyPin : Node->Pins)
		{
			if(MyPin->Direction == EGPD_Output)
			{
				for(auto OtherPin : MyPin->LinkedTo)
				{
					UEdGraphNode* OtherNode = OtherPin->GetOwningNode();

					if(VisitedNodes.Contains(OtherNode))
					{
						//Only an issue if this is a back-edge
						return false;
					}
					else if(!FinishedNodes.Contains(OtherNode))
					{
						//Only should traverse if this node hasn't been traversed
						if(!TraverseNodes(OtherNode))
						{
							return false;
						}
					}
				}
			}
		}

		VisitedNodes.Remove(Node);
		FinishedNodes.Add(Node);
		return true;
	}

private:
	TSet<UEdGraphNode*> VisitedNodes;
	TSet<UEdGraphNode*> FinishedNodes;
};

void UEdGraphSchema_KRGDialogue::GetBreakLinkToSubMenuActions(UToolMenu* Menu, UEdGraphPin* InEdGraphPin)
{
	//Make sure we have a unique name for every entry in the list
	TMap<FString, uint32> LinkTitleCount;

	FToolMenuSection& Section = Menu->FindOrAddSection("ATSGraphAssetGraphSchemaPinActions");

	//Add all the links we could break from
	for (TArray<class UEdGraphPin*>::TConstIterator Links(InEdGraphPin->LinkedTo); Links; ++Links)
	{
		UEdGraphPin* Pin = *Links;
		FString TitleString = Pin->GetOwningNode()->GetNodeTitle(ENodeTitleType::ListView).ToString();
		FText Title = FText::FromString(TitleString);
		if(Pin->PinName != TEXT(""))
		{
			TitleString = FString::Printf(TEXT("%s (%s)"), *TitleString, *Pin->PinName.ToString());

			//Add name of connection if possible
			FFormatNamedArguments Args;
			Args.Add(TEXT("NodeTitle"), Title);
			Args.Add(TEXT("PinName"), Pin->GetDisplayName());
			Title = FText::Format(FText::FromString("{NodeTitle} ({PinName})"), Args);
		}

		uint32& Count = LinkTitleCount.FindOrAdd(TitleString);

		FText Description;
		FFormatNamedArguments Args;
		Args.Add(TEXT("NodeTitle"), Title);
		Args.Add(TEXT("NumberOfNodes"), Count);

		if(Count == 0)
		{
			Description = FText::Format(FText::FromString(TEXT("Break link to {NodeTitle}")), Args);
		}
		else
		{
			Description = FText::Format(FText::FromString(TEXT("Break link to {NodeTitle} ({NumberOfNodes})")), Args);
		}

		++Count;

		Section.AddMenuEntry(NAME_None
			, Description, Description
			, FSlateIcon(), FUIAction(FExecuteAction::CreateUObject(this, &UEdGraphSchema_KRGDialogue::BreakSinglePinLink, const_cast<UEdGraphPin*>(InEdGraphPin)
			, *Links)));
	}
}

EGraphType UEdGraphSchema_KRGDialogue::GetGraphType(const UEdGraph* TestEdGraph) const
{
	return GT_StateMachine;
}

void UEdGraphSchema_KRGDialogue::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	UKRGDialogueGraph* Graph = CastChecked<UKRGDialogueGraph>(ContextMenuBuilder.CurrentGraph->GetOuter());

	if(false == Graph->IsValidNodeTypeClass())
	{
		return;
	}

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);

	const FText AddToolTip = FText::FromString(TEXT("Add node here"));

	TSet<TSubclassOf<UKRGDialogueNode>> Visited;

	FString Title = Graph->GetNodeTypeClass()->GetName();
	Title.RemoveFromEnd("_C");
	FText Desc = FText::FromString(Title);

	
	TSharedPtr<FEdGraphSchemaAction_KRGDialogueNew> NewFinishNodeAction(new FEdGraphSchemaAction_KRGDialogueNew(FText::FromString(TEXT("Node")), FText::FromString(TEXT("Script Node")), AddToolTip, 0));
	NewFinishNodeAction->CreateNodeTemplate(Graph, ContextMenuBuilder.OwnerOfTemporaries, UEdKRGDialogueNode_Script::StaticClass(), UKRGDialogueNode_Script::StaticClass());
	ContextMenuBuilder.AddAction(NewFinishNodeAction);

	Visited.Add(UKRGDialogueNode_Script::StaticClass());
	
	TSharedPtr<FEdGraphSchemaAction_KRGDialogueNew> NewCraftNodeAction(new FEdGraphSchemaAction_KRGDialogueNew(FText::FromString(TEXT("Node")), FText::FromString(TEXT("Branch Node")), AddToolTip, 0));
	NewCraftNodeAction->CreateNodeTemplate(Graph, ContextMenuBuilder.OwnerOfTemporaries, UEdKRGDialogueNode_Branch::StaticClass(), UKRGDialogueNode_Branch::StaticClass());
	ContextMenuBuilder.AddAction(NewCraftNodeAction);

	Visited.Add(UKRGDialogueNode_Branch::StaticClass());

	

	//클래스 생성 시 자동으로 추가해주는 구문 현재는 필요없어서 제거한다.
	/*
	for(TObjectIterator<UClass> It; It; ++It)
	{
		if(It->IsChildOf(UKRGDialogueNode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract) && !Visited.Contains(*It))
		{
			TSubclassOf<UKRGDialogueNode> NodeElementClass = *It;

			if(Visited.Contains(*It))
			{
				continue;
			}

			if(It->GetName().StartsWith("REINST") || It->GetName().StartsWith("SKEL"))
			{
				continue;
			}

			FString Title = NodeElementClass->GetName();
			Title.RemoveFromEnd("_C");
			Desc = FText::FromString(Title);

			TSharedPtr<FEdGraphSchemaAction_ATSBaseNew> NewAction(new FEdGraphSchemaAction_ATSBaseNew(FText::FromString(TEXT("Graph Node")), FText::FromString(TEXT("Base Node")), AddToolTip, 0));
			NewAction->CreateNodeTemplate(Graph, ContextMenuBuilder.OwnerOfTemporaries, UEdKRGDialogueNode::StaticClass(), NodeElementClass);
			ContextMenuBuilder.AddAction(NewAction);

			Visited.Add(NodeElementClass);
		}
	}
	*/
}

void UEdGraphSchema_KRGDialogue::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if(Context->Pin)
	{
		FToolMenuSection& Section = Menu->AddSection("EdGraphSchema_ATSBaseNodeActions", FText::FromString(TEXT("Pin Action")));
		//Only display the 'Break Links' option if there is a link to break!

		if(Context->Pin->LinkedTo.Num() > 0)
		{
			Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);

			//add sub menu for break link to
			if(Context->Pin->LinkedTo.Num() > 1)
			{
				Section.AddSubMenu(
					"BreakLinkTo"
					, FText::FromString(TEXT("Break Link to..."))
					, FText::FromString(TEXT("Break a specific link..."))
					, FNewToolMenuDelegate::CreateUObject((UEdGraphSchema_KRGDialogue* const)this, &UEdGraphSchema_KRGDialogue::GetBreakLinkToSubMenuActions, const_cast<UEdGraphPin*>(Context->Pin)));
			}
			else
			{
				((UEdGraphSchema_KRGDialogue* const)this)->GetBreakLinkToSubMenuActions(Menu, const_cast<UEdGraphPin*>(Context->Pin));
			}
		}
	}
	else if(Context->Node)
	{
		FToolMenuSection& Section = Menu->AddSection("EdGraphSchema_ATSBaseNodeActions",  FText::FromString(TEXT("Node Actions")));
		Section.AddMenuEntry(FGenericCommands::Get().Delete);
		Section.AddMenuEntry(FGenericCommands::Get().Cut);
		Section.AddMenuEntry(FGenericCommands::Get().Copy);
		Section.AddMenuEntry(FGenericCommands::Get().Duplicate);

		Section.AddMenuEntry(FGraphEditorCommands::Get().BreakNodeLinks);
	}

	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UEdGraphSchema_KRGDialogue::CanCreateConnection(const UEdGraphPin* A,
	const UEdGraphPin* B) const
{
	//Make sure the pins are not on the same node
	if(A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't connect node to itself"));
	}

	const UEdGraphPin* Out = A;
	const UEdGraphPin* In = B;

	UEdKRGDialogueNode* EdNode_Out = Cast<UEdKRGDialogueNode>(Out->GetOwningNode());
	UEdKRGDialogueNode* EdNode_In = Cast<UEdKRGDialogueNode>(In->GetOwningNode());

	if(false == IsValid(EdNode_In) || false == IsValid(EdNode_Out))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not a valid Graph EdNode"));
	}

	//Determine if we can have cyclces or not.
	bool bAllowCycles = false;
	auto EdGraph = Cast<UEdKRGDialogueGraph>(EdNode_Out->GetGraph());
	if(EdGraph != nullptr)
	{
		bAllowCycles = EdGraph->GetGraph()->bCanBeCyclical;
	}

	//check for cycles
	FNodeVisitorCyclceChecker CycleChecker;
	if(!bAllowCycles && !CycleChecker.CheckForLoop(Out->GetOwningNode(), In->GetOwningNode()))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Can't create a graph cycle"));
	}

	FText ErrorMessage;
	if(!EdNode_Out->GetNode()->CanCreateConnectionTo(EdNode_In->GetNode(), ErrorMessage))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
	}
	if(!EdNode_In->GetNode()->CanCreateConnectionFrom(EdNode_Out->GetNode(), ErrorMessage))
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, ErrorMessage);
	}

	if(EdNode_Out->GetNode()->GetGraph()->IsEdgeEnabled())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, TEXT("Connect nodes with edge"));
	}
	else
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT("Connect nodes"));
	}
}

bool UEdGraphSchema_KRGDialogue::TryCreateConnection(UEdGraphPin* A, UEdGraphPin* B) const
{
	//We don't actually care about the pin, we want the node that is being dragged between
	UEdKRGDialogueNode* NodeA = Cast<UEdKRGDialogueNode>(A->GetOwningNode());
	UEdKRGDialogueNode* NodeB = Cast<UEdKRGDialogueNode>(B->GetOwningNode());

	if(nullptr == NodeA
		|| nullptr == NodeB)
	{
		return false;
	}

	//check that this edge doesn't already exist
	for(UEdGraphPin* TestPin : NodeA->GetOutputPin()->LinkedTo)
	{
		UEdGraphNode* ChildNode = TestPin->GetOwningNode();
		if(UEdKRGDialogueEdge* EdEdge = Cast<UEdKRGDialogueEdge>(ChildNode))
		{
			ChildNode = EdEdge->GetEdEndNode();
		}

		if(ChildNode == NodeB)
		{
			return false;
		}
	}

	if(NodeA && NodeB)
	{
		//Always create connections from node A to B, don't allow adding in reversee

		UEdGraphPin* ToPin = NodeA->GetOutputPin();
		UEdGraphPin* FromPin = NodeB->GetInputPin();
		
		if(NodeA->IsA(UEdKRGDialogueNode_Branch::StaticClass()))
		{
			ToPin = A;
		}
		else if(NodeB->IsA(UEdKRGDialogueNode_Script::StaticClass()))
		{
			FromPin = B;
		}
		
		Super::TryCreateConnection(ToPin, FromPin);

		return true;
	}

	return false;
}

bool UEdGraphSchema_KRGDialogue::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* A, UEdGraphPin* B) const
{
	UEdKRGDialogueNode* NodeA = Cast<UEdKRGDialogueNode>(A->GetOwningNode());
	UEdKRGDialogueNode* NodeB = Cast<UEdKRGDialogueNode>(B->GetOwningNode());

	//Are nodes and pins all valid?
	if(!NodeA || !NodeA->GetOutputPin() || !NodeB || !NodeB->GetInputPin())
	{
		return false;
	}

	UKRGDialogueGraph* Graph = NodeA->GetNode()->GetGraph();

	FVector2D InitPos((NodeA->NodePosX + NodeB->NodePosX) / 2, (NodeA->NodePosY + NodeB->NodePosY) / 2);

	
	FEdGraphSchemaAction_KRGDialogueNew Action;
	Action.CreateNodeTemplate(Graph, NodeA->GetGraph(), UEdKRGDialogueEdge::StaticClass(), UKRGDialogueEdge::StaticClass());
	UEdKRGDialogueEdge* EdEdge = Cast<UEdKRGDialogueEdge>(Action.PerformAction(NodeA->GetGraph(), nullptr, InitPos, false));

	//Always create connections from node A to B, don't allow adding in reverse
	EdEdge->CreateConnections(NodeA, NodeB);

	return true;
}

FConnectionDrawingPolicy* UEdGraphSchema_KRGDialogue::CreateConnectionDrawingPolicy(int32 InBackLayerID,
	int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, FSlateWindowElementList& InDrawElements,
	UEdGraph* InGraphObj) const
{
	//return Super::CreateConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect,
	//                                            InDrawElements, InGraphObj);

	return new FConnectionDrawingPolicy_KRGDialogueBase(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	//return new FConnectionDrawingPolicy_ATSStraight(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

FLinearColor UEdGraphSchema_KRGDialogue::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

void UEdGraphSchema_KRGDialogue::BreakNodeLinks(UEdGraphNode& TargetNode) const
{
	const FScopedTransaction Transaction(FText::FromString(TEXT("Break Node Links")));
}

void UEdGraphSchema_KRGDialogue::BreakPinLinks(UEdGraphPin& TargetPin, bool bSendsNodeNotifcation) const
{
	const FScopedTransaction Transaction(FText::FromString(TEXT("Break Pin Links")));

	Super::BreakPinLinks(TargetPin, bSendsNodeNotifcation);
}

void UEdGraphSchema_KRGDialogue::BreakSinglePinLink(UEdGraphPin* SourcePin, UEdGraphPin* TargetPin) const
{
	const FScopedTransaction Transaction(FText::FromString(TEXT("Break Pin Link")));
	
	Super::BreakSinglePinLink(SourcePin, TargetPin);
}

UEdGraphPin* UEdGraphSchema_KRGDialogue::DropPinOnNode(UEdGraphNode* InTargetNode, const FName& InSourcePinName,
	const FEdGraphPinType& InSourcePinType, EEdGraphPinDirection InSourcePinDirection) const
{
	UEdKRGDialogueNode* EdNode = Cast<UEdKRGDialogueNode>(InTargetNode);

	switch (InSourcePinDirection)
	{
	case EGPD_Input :
		return EdNode->GetOutputPin();
	case EGPD_Output :
		return EdNode->GetInputPin();
	}

	return nullptr;
}

bool UEdGraphSchema_KRGDialogue::SupportsDropPinOnNode(UEdGraphNode* InTargetNode, const FEdGraphPinType& InSourcePinType,
	EEdGraphPinDirection InSourcePinDirection, FText& OutErrorMessage) const
{
	return Cast<UEdGraphSchema_KRGDialogue>(InTargetNode) != nullptr;
}

bool UEdGraphSchema_KRGDialogue::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UEdGraphSchema_KRGDialogue::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UEdGraphSchema_KRGDialogue::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}
