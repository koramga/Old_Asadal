#include "EdGraphSchemaAction_KRGDialogueNew.h"

UEdGraphNode* FEdGraphSchemaAction_KRGDialogueNew::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin,
	const FVector2D Location, bool bSelectNewNode)
{
	UEdGraphNode* ResultNode = nullptr;

	if(NodeTemplate != nullptr)
	{
		const FScopedTransaction Transaction(FText::FromString("ATS Graph Editor : New Node"));
		ParentGraph->Modify();
		if(FromPin != nullptr)
			FromPin->Modify();

		NodeTemplate->Rename(nullptr, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;

		NodeTemplate->SetTemplateFlag(RF_Transactional);
		NodeTemplate->SetFlags(RF_Transactional);

		ResultNode = NodeTemplate;
	}

	return ResultNode;
}

void FEdGraphSchemaAction_KRGDialogueNew::AddReferencedObjects(FReferenceCollector& Collector)
{
	FEdGraphSchemaAction::AddReferencedObjects(Collector);
	Collector.AddReferencedObject(NodeTemplate);
}

void FEdGraphSchemaAction_KRGDialogueNew::CreateElementTemplate(UKRGDialogueGraph* Graph, UEdGraph* Owner,
	TSubclassOf<UEdKRGDialogueElement> ElementTemplateClass, TSubclassOf<UKRGDialogueElement> GraphElementClass)
{
	check(Owner);
	check(ElementTemplateClass);
	NodeTemplate = NewObject<UEdKRGDialogueElement>(Owner, ElementTemplateClass);
	NodeTemplate->SetGraphElement(NodeTemplate, GraphElementClass);
	UKRGDialogueElement* GraphElement = NodeTemplate->GetGraphElement();
	check(GraphElement);	
	GraphElement->SetGraph(Graph);
	
}
