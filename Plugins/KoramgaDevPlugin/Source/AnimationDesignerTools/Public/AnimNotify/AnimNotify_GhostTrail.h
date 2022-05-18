// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AnimNotify_GhostTrail.generated.h"

/**
 * 
 */
UCLASS()
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
};
