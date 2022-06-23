// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element/Node/KRGDialogueNode.h"
#include "Node/EdKRGDialogueElement.h"
#include "EdKRGDialogueNode.generated.h"

class UKRGDialogueNode;
class UEdKRGDialogueGraph;
class SEdKRGDialogueNode;

/**
 * 
 */
UCLASS(Abstract)
class KRGDIALOGUEEDITOR_API UEdKRGDialogueNode : public UEdKRGDialogueElement
{
	GENERATED_BODY()

public:
	UEdKRGDialogueNode();
	virtual ~UEdKRGDialogueNode();

	UKRGDialogueNode* GetNode() const;
	void SetNode(UKRGDialogueNode* InNode);
	void SetSEdNode(SEdKRGDialogueNode* InSEdNode);
	UEdKRGDialogueGraph* GetEdGraph();
	
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;
	virtual bool CanUserDeleteNode() const override;

	virtual FLinearColor GetBackgroundColor() const;
	virtual UEdGraphPin* GetInputPin() const;
	virtual UEdGraphPin* GetOutputPin() const;

	

#if WITH_EDITOR
	virtual void PostEditUndo() override;
#endif

protected:
	SEdKRGDialogueNode* SEdNode;
};
