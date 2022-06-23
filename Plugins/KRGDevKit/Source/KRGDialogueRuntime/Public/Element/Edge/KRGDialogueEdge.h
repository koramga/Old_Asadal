// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element/KRGDialogueElement.h"
#include "KRGDialogueEdge.generated.h"

/**
 * 
 */

class UKRGDialogueGraph;
class UKRGDialogueNode;

UCLASS(Blueprintable)
class KRGDIALOGUERUNTIME_API UKRGDialogueEdge : public UKRGDialogueElement
{
	GENERATED_BODY()
	
public :
	UKRGDialogueEdge();
	virtual ~UKRGDialogueEdge();

protected:
	UPROPERTY(BlueprintReadOnly, Category="KRGDialogueEdge")
	UKRGDialogueNode* StartNode;

	UPROPERTY(BlueprintReadOnly, Category="KRGDialogueEdge")
	UKRGDialogueNode* EndNode;

public:
	UKRGDialogueNode* GetStartNode() const;
	UKRGDialogueNode* GetEndNode() const;

	void SetStartNode(UKRGDialogueNode* InStartNode);
	void SetEndNode(UKRGDialogueNode* InEndNode);

#if WITH_EDITORONLY_DATA

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueEdge_Editor")
	bool bShouldDrawTitle = false;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueEdge_Editor")
	FText NodeTitle;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueEdge")
	FLinearColor EdgeColor = FLinearColor(0.9f, 0.9f, 0.9f, 1.f);
	
#endif

#if WITH_EDITOR

	virtual FText GetNodeTitle() const { return NodeTitle;}
	FLinearColor GetEdgeColor() { return EdgeColor;}

	virtual void SetNodeTitle(const FText& NewTitle);
	
#endif
};
