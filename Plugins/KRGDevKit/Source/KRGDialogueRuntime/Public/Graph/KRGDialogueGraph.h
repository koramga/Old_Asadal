// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Element/Edge/KRGDialogueEdge.h"
#include "Element/Node/KRGDialogueNode.h"
#include "UObject/NoExportTypes.h"
#include "KRGDialogueGraph.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class KRGDIALOGUERUNTIME_API UKRGDialogueGraph : public UObject
{
	GENERATED_BODY()

public :
	UKRGDialogueGraph();
	virtual ~UKRGDialogueGraph();

protected:
	UPROPERTY(EditDefaultsOnly, Category="KRGDialogue")
	FString Name;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogue")
	TSubclassOf<UKRGDialogueNode>	NodeType;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogue")
	TSubclassOf<UKRGDialogueEdge>	EdgeType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="KRGDialogue")
	FGameplayTagContainer	GraphTags;

	UPROPERTY(BlueprintReadOnly, Category="KRGDialogue")
	TArray<UKRGDialogueNode*> RootNodes;

	UPROPERTY(BlueprintReadOnly, Category="KRGDialogue")
	TArray<UKRGDialogueNode*> AllNodes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="KRGDialogue")
	bool bIsEdgeEnabled;
	
	UPROPERTY(VisibleAnywhere)
	FString						EditorToolkitName;

public :
	void SetEditorToolkitName(const FString& ToolkitName);
	FString GetEditorToolkitName() const;
	
	FString GetName() const;
	void SetName(const FString& InName);

	bool IsValidNodeTypeClass() const;
	TSubclassOf<UKRGDialogueNode>& GetNodeTypeClass();

	bool IsValidEdgeTypeClass() const;
	TSubclassOf<UKRGDialogueEdge>& GetEdgeTypeClass();
	

	bool IsEdgeEnabled() const;
	void SetEdgeEnabled(bool InbIsEdgeEnabled);

	const TArray<UKRGDialogueNode*>& GetAllNodes() const;
	void AddNode(UKRGDialogueNode* KRGDialogueNode);
	void AddRootNode(UKRGDialogueNode* InNode);
	TArray<UKRGDialogueNode*>& GetRootNodes();
	
public :
	UFUNCTION(BlueprintCallable, Category="KRGDialogue")
	void Print(bool ToConsole = true, bool ToScreen = true);

	UFUNCTION(BlueprintCallable, Category="KRGDialogue")
	int GetLevelNum() const;

	UFUNCTION(BlueprintCallable, Category="KRGDialogue")
	void GetNodesByLevel(int Level, TArray<UKRGDialogueNode*>& Nodes);

	void ClearGraph();

public :
	virtual void OnBuildEnd();

#if WITH_EDITORONLY_DATA
	UPROPERTY()
	class UEdGraph* EdGraph;

	UPROPERTY(EditDefaultsOnly, Category = "KRGDialogue_Editor")
	bool bCanRenameNode;

	UPROPERTY(EditDefaultsOnly, Category = "KRGDialogue_Editor")
	bool bCanBeCyclical;
#endif
};
