// Fill out your copyright notice in the Description page of Project Settings.


#include "Graph/KRGDialogueGraph.h"
#include "KRGDialogueRuntimePCH.h"
#include "Element/Edge/KRGDialogueEdge.h"
#include "Element/Node/KRGDialogueNode.h"

#define LOCTEXT_NAMESPACE "KRGDialogue"

UKRGDialogueGraph::UKRGDialogueGraph()
{
	NodeType = UKRGDialogueNode::StaticClass();
	EdgeType = UKRGDialogueEdge::StaticClass();

	bIsEdgeEnabled = true;

#if WITH_EDITORONLY_DATA

	EdGraph = nullptr;
	
	bCanRenameNode = true;
	
#endif
}

UKRGDialogueGraph::~UKRGDialogueGraph()
{
	
}

void UKRGDialogueGraph::SetEditorToolkitName(const FString& ToolkitName)
{
	EditorToolkitName = ToolkitName;
}

FString UKRGDialogueGraph::GetEditorToolkitName() const
{
	return EditorToolkitName;
}

FString UKRGDialogueGraph::GetName() const
{
	return Name;
}

void UKRGDialogueGraph::SetName(const FString& InName)
{
	Name = InName;
}

bool UKRGDialogueGraph::IsValidNodeTypeClass() const
{
	if(IsValid(NodeType))
	{
		return true;
	}

	return false;
}

TSubclassOf<UKRGDialogueNode>& UKRGDialogueGraph::GetNodeTypeClass()
{
	return NodeType;
}

bool UKRGDialogueGraph::IsValidEdgeTypeClass() const
{
	if(IsValid(EdgeType))
	{
		return true;
	}

	return false;
}

TSubclassOf<UKRGDialogueEdge>& UKRGDialogueGraph::GetEdgeTypeClass()
{
	return EdgeType;
}

bool UKRGDialogueGraph::IsEdgeEnabled() const
{
	return bIsEdgeEnabled;
}

void UKRGDialogueGraph::SetEdgeEnabled(bool InbIsEdgeEnabled)
{
	bIsEdgeEnabled = InbIsEdgeEnabled;
}

const TArray<UKRGDialogueNode*>& UKRGDialogueGraph::GetAllNodes() const
{
	return AllNodes;
}

void UKRGDialogueGraph::AddNode(UKRGDialogueNode* KRGDialogueNode)
{
	AllNodes.Add(KRGDialogueNode);
}

void UKRGDialogueGraph::AddRootNode(UKRGDialogueNode* InNode)
{
	RootNodes.Add(InNode);
}

TArray<UKRGDialogueNode*>& UKRGDialogueGraph::GetRootNodes()
{
	return RootNodes;
}

void UKRGDialogueGraph::Print(bool ToConsole, bool ToScreen)
{
	int32 Level = 0;
	TArray<UKRGDialogueNode*> CurrLevelNodes = RootNodes;
	TArray<UKRGDialogueNode*> NextLevelNodes;

	while(CurrLevelNodes.Num() != 0)
	{
		for(int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UKRGDialogueNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			FString Message = FString::Printf(TEXT("%s, Level %d"), *Node->GetDescription().ToString(), Level);

			if(ToConsole)
			{
				LOG_INFO(TEXT("%s"), *Message);
			}

			if(ToScreen && GEngine != nullptr)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Blue, Message);
			}

			const TArray<UKRGDialogueNode*>& ChildrenNodeFromNode = Node->GetChildrenNodes();
			
			for(UKRGDialogueNode* ChildNode : ChildrenNodeFromNode)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
}

int UKRGDialogueGraph::GetLevelNum() const
{
	int32 Level = 0;
	TArray<UKRGDialogueNode*> CurrLevelNodes = RootNodes;
	TArray<UKRGDialogueNode*> NextLevelNodes;

	while (CurrLevelNodes.Num() != 0)
	{
		for (int i = 0; i < CurrLevelNodes.Num(); ++i)
		{
			UKRGDialogueNode* Node = CurrLevelNodes[i];
			check(Node != nullptr);

			const TArray<UKRGDialogueNode*>& ChildrenNodeFromNode = Node->GetChildrenNodes();
			
			for (UKRGDialogueNode* ChildNode : ChildrenNodeFromNode)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}

		CurrLevelNodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++Level;
	}
	
	return Level;
}

void UKRGDialogueGraph::GetNodesByLevel(int Level, TArray<UKRGDialogueNode*>& Nodes)
{
	int CurrLEvel = 0;
	TArray<UKRGDialogueNode*> NextLevelNodes;

	Nodes = RootNodes;

	while (Nodes.Num() != 0)
	{
		if (CurrLEvel == Level)
			break;

		for (int i = 0; i < Nodes.Num(); ++i)
		{
			UKRGDialogueNode* Node = Nodes[i];
			check(Node != nullptr);

			const TArray<UKRGDialogueNode*>& ChildrenNodeFromNode = Node->GetChildrenNodes();

			for (UKRGDialogueNode* ChildNode : ChildrenNodeFromNode)
			{
				NextLevelNodes.Add(ChildNode);
			}
		}

		Nodes = NextLevelNodes;
		NextLevelNodes.Reset();
		++CurrLEvel;
	}
}

void UKRGDialogueGraph::ClearGraph()
{
	for (int i = 0; i < AllNodes.Num(); ++i)
	{
		UKRGDialogueNode* Node = AllNodes[i];
		if (nullptr != Node)
		{
			Node->Clear();			
		}
	}

	AllNodes.Empty();
	RootNodes.Empty();
}

void UKRGDialogueGraph::OnBuildEnd()
{
}

#undef LOCTEXT_NAMESPACE
