// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "AnimNotify_GameplayTags.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EAnimNotifyGameplayTagCommand : uint8
{
	Add,
	Remove,
};

USTRUCT(BlueprintType)
struct FAnimNotifyGameplayTagCommand
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EAnimNotifyGameplayTagCommand	Command;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer			GameplayTagContainer;
};

UCLASS(editinlinenew, Blueprintable, const, hidecategories = Object, collapsecategories, meta = (ShowWorldContextPin, DisplayName = "GameplayTags"))
class ANIMATIONDESIGNERTOOLS_API UAnimNotify_GameplayTags : public UAnimNotify
{
	GENERATED_BODY()
	
public :
	UAnimNotify_GameplayTags();
	
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FAnimNotifyGameplayTagCommand>	GameplayTagCommands;
};
