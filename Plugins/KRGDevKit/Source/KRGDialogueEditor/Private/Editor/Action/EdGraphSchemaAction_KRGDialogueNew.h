#pragma once

#include "CoreMinimal.h"
#include "Node/Node/EdKRGDialogueNode.h"
#include "EdGraphSchemaAction_KRGDialogueNew.generated.h"

USTRUCT()
struct FEdGraphSchemaAction_KRGDialogueNew : public FEdGraphSchemaAction
{
	GENERATED_USTRUCT_BODY();
	
	FEdGraphSchemaAction_KRGDialogueNew()
		: NodeTemplate(nullptr) {}

	FEdGraphSchemaAction_KRGDialogueNew(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NodeTemplate(nullptr){}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode) override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual void CreateNodeTemplate(UKRGDialogueGraph* Graph, UEdGraph* Owner, TSubclassOf<UEdKRGDialogueNode> NodeTemplateClass, TSubclassOf<UKRGDialogueElement> GraphElementClass);
	
protected:
	UEdKRGDialogueNode* NodeTemplate;
};
