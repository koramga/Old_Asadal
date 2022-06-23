#include "KRGDialogueElementFactory.h"

#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Edge/Slate/SEdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode_Branch.h"
#include "Node/Node/EdKRGDialogueNode_Script.h"
#include "Node/Node/Slate/SEdKRGDialogueNode_Branch.h"
#include "Node/Node/Slate/SEdKRGDialogueNode_Script.h"

TSharedPtr<SGraphNode> FKRGDialogueElementFactory::CreateNode(UEdGraphNode* Node) const
{
	if(UEdKRGDialogueNode_Branch* EdCraftNode = Cast<UEdKRGDialogueNode_Branch>(Node))
	{
		return SNew(SEdKRGDialogueNode_Branch)
			.EdGraphNode(Node);		
	}
	else if(UEdKRGDialogueNode_Script* EdGeneralNode = Cast<UEdKRGDialogueNode_Script>(Node))
	{
		return SNew(SEdKRGDialogueNode_Script)
			.EdGraphNode(Node);
	}
	else if(UEdKRGDialogueEdge* EdBaseEdge = Cast<UEdKRGDialogueEdge>(Node))
	{
		return SNew(SEdKRGDialogueEdge)
			.EdGraphNode(Node);
	}

	return nullptr;
}
