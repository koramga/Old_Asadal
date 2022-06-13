// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGVariable.h"
#include "AnimNotify_GhostTrail.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FGhostTrailMaterial
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32				ElementIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UMaterial*			Material;
	
};

UCLASS(editinlinenew, Blueprintable, const, hidecategories = Object, collapsecategories, meta = (ShowWorldContextPin, DisplayName = "GhostTrail"))
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_GhostTrail : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	UAnimNotify_GhostTrail();
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual FString GetNotifyName_Implementation() const override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	LifeTime = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FGhostTrailMaterial>			GhostTrailMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKRGMaterialInstanceVariable>	MaterialInstanceVariables;
};
