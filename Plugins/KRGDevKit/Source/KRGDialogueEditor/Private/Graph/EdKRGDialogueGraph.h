// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EdKRGDialogueGraph.generated.h"

/**
 * 
 */

class UKRGDialogueGraph;
class UKRGDialogueNode;
class UKRGDialogueEdge;
class UEdKRGDialogueNode;
class UEdKRGDialogueEdge;

UCLASS()
class KRGDIALOGUEEDITOR_API UEdKRGDialogueGraph : public UEdGraph
{
	GENERATED_BODY()

public :
	UEdKRGDialogueGraph();
	virtual ~UEdKRGDialogueGraph();

	//virtual void RebuildGraph(class FAssetEditor_ATSGraph* AssetEditor_ATSGraph);
	UKRGDialogueGraph* GetGraph() const;

	virtual bool Modify(bool bAlwaysMarkDirty) override;
	virtual void PostEditUndo() override;

	UPROPERTY(Transient)
	TMap<UKRGDialogueNode*, UEdKRGDialogueNode*> NodeMap;

	UPROPERTY(Transient)
	TMap<UKRGDialogueEdge*, UEdKRGDialogueEdge*>	EdgeMap;

protected:
	void Clear();
	void SortNodes(UKRGDialogueNode* RootNode);
};
