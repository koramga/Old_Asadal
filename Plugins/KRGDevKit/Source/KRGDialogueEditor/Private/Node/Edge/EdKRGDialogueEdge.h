// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Node/EdKRGDialogueElement.h"
#include "EdKRGDialogueEdge.generated.h"

/**
 * 
*/

class UKRGDialogueGraph;
class UKRGDialogueNode;
class UKRGDialogueEdge;
class UEdKRGDialogueNode;

UCLASS()
class KRGDIALOGUEEDITOR_API UEdKRGDialogueEdge : public UEdKRGDialogueElement
{
	GENERATED_BODY()

public :
	UEdKRGDialogueEdge();

	void SetEdge(UKRGDialogueEdge* InEdge);
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PinConnectionListChanged(UEdGraphPin* Pin) override;
	virtual void PrepareForCopying() override;

	virtual UEdGraphPin* GetInputPin() const { return Pins[0]; }
	virtual UEdGraphPin* GetOutputPin() const { return Pins[1]; }

	void CreateConnections(UEdKRGDialogueNode* Start, UEdKRGDialogueNode* End);

	UEdKRGDialogueNode* GetEdStartNode() const;
	UEdKRGDialogueNode* GetEdEndNode() const;

	UKRGDialogueEdge* GetEdge() const;

	public :
		virtual void SetTemplateFlag(EObjectFlags NewFlags) override;

protected:
	UPROPERTY()
	class UEdGraph* Graph;
};
