// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Element/KRGDialogueElement.h"
#include "KRGDialogueNode.generated.h"

/**
 * 
*/
class UKRGDialogueGraph;
class UKRGDialogueEdge;

UCLASS(Blueprintable)
class KRGDIALOGUERUNTIME_API UKRGDialogueNode : public UKRGDialogueElement
{
	GENERATED_BODY()
	
public :
	UKRGDialogueNode();
	virtual ~UKRGDialogueNode();

protected:	
	UPROPERTY(VisibleDefaultsOnly, Category="KRGDialogueNode")
	TArray<UKRGDialogueNode*> ParentNodes;

	UPROPERTY(VisibleDefaultsOnly, Category="KRGDialogueNode")
	TArray<UKRGDialogueNode*> ChildrenNodes;

	UPROPERTY(VisibleDefaultsOnly, Category="KRGDialogueNode")
	TMap<UKRGDialogueNode*, UKRGDialogueEdge*> Edges;

public :
	TArray<UKRGDialogueNode*>& GetChildrenNodes();
	TArray<UKRGDialogueNode*>& GetParentNodes();
	void Clear();

	void AddChildNode(UKRGDialogueNode* ChildNode);
	void RemoveChildNode(UKRGDialogueNode* ChildNode);
	void ClearChildNodes();
	bool IsEmptyChildNode() const;
	void AddParentNode(UKRGDialogueNode* ParentNode);
	void RemoveParentNode(UKRGDialogueNode* ParentNode);
	void ClearParentNodes();
	bool IsEmptyParentNode() const;
	void AddEdge(UKRGDialogueNode* InNode, UKRGDialogueEdge* InEdge);
	void ClearEdges();

	virtual bool CanUserDeleteNode();
	
public :
	UFUNCTION(BlueprintCallable, Category="KRGDialogueNode")
	virtual UKRGDialogueEdge* GetEdge(UKRGDialogueNode* ChildNode);
	
	UFUNCTION(BlueprintCallable, Category="KRGDialogueNode")
	bool IsLeafNode() const;

	UFUNCTION(BlueprintCallable, Category="KRGDialogueNode")
	bool IsRootNode() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="KRGDialogueNode")
	FText GetDescription() const;
	virtual FText GetDescription_Implementation() const;

#if WITH_EDITORONLY_DATA
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor")
	FText NodeTitle;
	
	UPROPERTY(VisibleDefaultsOnly, Category="KRGDialogueNode_Editor")
	TSubclassOf<UKRGDialogueNode> CompatibleGraphType;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor")
	FLinearColor BackgroundColor;

	UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor")
	FText ContextMenuName;

	//UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor")
	//ENodeLimit ParentLimitType;

	//UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor", meta = (ClampMin = "0",EditCondition = "ParentLimitType == ENodeLimit::Limited", EditConditionHides))
	//int32 ParentLimit;

	//UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor")
	//ENodeLimit ChildrenLimitType;

	//UPROPERTY(EditDefaultsOnly, Category="KRGDialogueNode_Editor", meta = (ClampMin = "0",EditCondition = "ParentLimitType == ENodeLimit::Limited", EditConditionHides))
	//int32 ChildrenLimit;
	
#endif

#if WITH_EDITOR
public :
	virtual bool IsNameEditable() const;
	virtual FLinearColor GetBackgroundColor() const;
	virtual FText GetNodeTitle() const;
	virtual FText GetContextMenuName() const;
	const TSubclassOf<UKRGDialogueNode>& GetCompatibleGraphType() const;
	virtual void SetNodeTitle(const FText& NewTitle);
	virtual bool CanCreateConnection(UKRGDialogueNode* Other, FText& ErrorMessage);
	virtual bool CanCreateConnectionTo(UKRGDialogueNode* Other, int32 NumberOfChildrenNodes, FText& ErrorMessage);
	virtual bool CanCreateConnectionFrom(UKRGDialogueNode* Other, int32 NumberOfParentNodes, FText& ErrorMessage);
#endif
};
