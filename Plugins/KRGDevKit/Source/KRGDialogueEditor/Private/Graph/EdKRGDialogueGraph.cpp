// Fill out your copyright notice in the Description page of Project Settings.


#include "EdKRGDialogueGraph.h"
#include "KRGDialogueEditorPCH.h"
#include "Graph/KRGDialogueGraph.h"
#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode.h"
#include "Editor/AssetEditor_KRGDialogueGraph.h"

UEdKRGDialogueGraph::UEdKRGDialogueGraph()
{
}

UEdKRGDialogueGraph::~UEdKRGDialogueGraph()
{
}

void UEdKRGDialogueGraph::RebuildGraph(FAssetEditor_KRGDialogueGraph* AssetEditor_ATSGraph)
{
	LOG_INFO(TEXT("RebuildGraph has been called"));

	UKRGDialogueGraph* Graph = GetGraph();

	Graph->SetEditorToolkitName(AssetEditor_ATSGraph->GetToolkitName().ToString());

	Clear();
	
	for(int i = 0; i < Nodes.Num(); ++i)
	{
		if(UEdKRGDialogueNode* EdNode = Cast<UEdKRGDialogueNode>(Nodes[i]))
		{
			UKRGDialogueNode* Node = EdNode->GetNode();

			if(Node != nullptr)
			{
				NodeMap.Add(Node, EdNode);

				Graph->AddNode(Node);

				for(int PinIdx = 0; PinIdx < EdNode->Pins.Num(); ++PinIdx)
				{
					UEdGraphPin* Pin = EdNode->Pins[PinIdx];

					if(Pin->Direction != EGPD_Output)
					{
						continue;
					}

					for(int LinkToIdx = 0; LinkToIdx < Pin->LinkedTo.Num(); ++LinkToIdx)
					{
						UKRGDialogueNode* ChildNode = nullptr;
						if(UEdKRGDialogueNode* EdNode_Child = Cast<UEdKRGDialogueNode>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
						{
							ChildNode = EdNode_Child->GetNode();
						}
						else if(UEdKRGDialogueEdge* EdNode_Edge = Cast<UEdKRGDialogueEdge>(Pin->LinkedTo[LinkToIdx]->GetOwningNode()))
						{
							UEdKRGDialogueNode* Child = EdNode_Edge->GetEdEndNode();

							if(Child != nullptr)
							{
								ChildNode = Child->GetNode();
							}
						}

						if(ChildNode != nullptr)
						{
							ChildNode->AddParentNode(Node);							
							Node->AddChildNode(ChildNode);
						}
						else
						{
							LOG_ERROR(TEXT("UEdKRGDialogueGraph::RebuildGraph can't find child node"));
						}
					}
				}
			}
		}
		else if(UEdKRGDialogueEdge* EdEdge = Cast<UEdKRGDialogueEdge>(Nodes[i]))
		{
			UEdKRGDialogueNode* StartNode = EdEdge->GetEdStartNode();
			UEdKRGDialogueNode* EndNode = EdEdge->GetEdEndNode();
			UKRGDialogueEdge* Edge = EdEdge->GetEdge();

			if(StartNode == nullptr || EndNode == nullptr || Edge == nullptr)
			{
				LOG_ERROR(TEXT("UEdKRGDialogueGraph::RebuildGraph add edge failed."));
				continue;
			}

			EdgeMap.Add(Edge, EdEdge);

			Edge->SetGraph(Graph);
			Edge->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
			Edge->SetStartNode(StartNode->GetNode());
			Edge->SetEndNode(EndNode->GetNode());
			//가는 방향으로 되니까 StartNode에만 담자.
			Edge->GetStartNode()->AddEdge(Edge->GetEndNode(), Edge);
		}
	}

	const TArray<UKRGDialogueNode*>& AllNodes = Graph->GetAllNodes();
	
	for(int i = 0; i < AllNodes.Num(); ++i)
	{
		UKRGDialogueNode* Node = AllNodes[i];

		if(Node->IsRootNode())
		{
			Graph->AddRootNode(Node);

			SortNodes(Node);
		}

		Node->SetGraph(Graph);
		Node->Rename(nullptr, Graph, REN_DontCreateRedirectors | REN_DoNotDirty);
	}

	Graph->OnBuildEnd();
	
	//TFunctionRef<bool> Comp = [&](const UKRGDialogueNode& L, const UKRGDialogueNode& R)
	//{
	//	UEdKRGDialogueNode* EdNode_LNode = NodeMap[&L];
	//	UEdKRGDialogueNode* EdNode_RNode = NodeMap[&R];
	//	return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
	//};
	//
	//Graph->SortRootNodes(Comp);
}

UKRGDialogueGraph* UEdKRGDialogueGraph::GetGraph() const
{
	return CastChecked<UKRGDialogueGraph>(GetOuter());
}

bool UEdKRGDialogueGraph::Modify(bool bAlwaysMarkDirty)
{
	bool Rtn = Super::Modify(bAlwaysMarkDirty);

	GetGraph()->Modify();

	for(int32 i = 0; i < Nodes.Num(); ++i)
	{
		Nodes[i]->Modify();
	}

	return Rtn;
}

void UEdKRGDialogueGraph::PostEditUndo()
{
	Super::PostEditUndo();

	NotifyGraphChanged();
}

void UEdKRGDialogueGraph::Clear()
{
	UKRGDialogueGraph* Graph = GetGraph();

	Graph->ClearGraph();
	NodeMap.Reset();
	EdgeMap.Reset();

	for(int i = 0; i < Nodes.Num(); ++i)
	{
		if(UEdKRGDialogueNode* EdNode = Cast<UEdKRGDialogueNode>(Nodes[i]))
		{
			UKRGDialogueNode* Node = EdNode->GetNode();

			if(nullptr != Node)
			{
				Node->ClearParentNodes();
				Node->ClearChildNodes();
				Node->ClearEdges();
			}
		}
	}
}

void UEdKRGDialogueGraph::SortNodes(UKRGDialogueNode* RootNode)
{
	int Level = 0;
	TArray<UKRGDialogueNode*> CurrLevelNodes = {RootNode};
	TArray<UKRGDialogueNode*> NextLevelNodes;

	while(CurrLevelNodes.Num() != 0)
	{
		int32 LevelWidth = 0;

		for(int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UKRGDialogueNode* Node = CurrLevelNodes[i];

			//TFunctionRef<bool> Comp = [&](const UKRGDialogueNode& L, const UKRGDialogueNode& R)
			//{
			//	UEdKRGDialogueNode* EdNode_LNode = NodeMap[&L];
			//	UEdKRGDialogueNode* EdNode_RNode = NodeMap[&R];
			//	return EdNode_LNode->NodePosX < EdNode_RNode->NodePosX;
			//};
			//
			//Node->SortChildrenNodes(Comp);
			//Node->SortParentNodes(Comp);

			const TArray<UKRGDialogueNode*>& ChildrenNode = Node->GetChildrenNodes();
			
			for(UKRGDialogueNode* ChildNode : ChildrenNode)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}
