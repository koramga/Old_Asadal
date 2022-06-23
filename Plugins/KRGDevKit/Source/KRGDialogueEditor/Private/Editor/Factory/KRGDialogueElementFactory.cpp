#include "KRGDialogueElementFactory.h"

TSharedPtr<SGraphNode> FKRGDialogueElementFactory::CreateNode(UEdGraphNode* Node) const
{
	//if(UEdGraphNode_ATSCraftNode* EdCraftNode = Cast<UEdGraphNode_ATSCraftNode>(Node))
	//{
	//	return SNew(SEdGraphNode_ATSCraftNode)
	//		.EdGraphNode(Node);		
	//}
	//else if(UEdGraphNode_ATSGeneralNode* EdGeneralNode = Cast<UEdGraphNode_ATSGeneralNode>(Node))
	//{
	//	return SNew(SEdGraphNode_ATSGeneralNode)
	//		.EdGraphNode(Node);
	//}
	//else if(UEdGraphNode_ATSBaseEdge* EdBaseEdge = Cast<UEdGraphNode_ATSBaseEdge>(Node))
	//{
	//	return SNew(SEdGraphNode_ATSBaseEdge)
	//		.EdGraphNode(Node);
	//}

	return nullptr;
}
