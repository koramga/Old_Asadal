// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState_Trail.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
#include "UObject/Object.h"
#include "AnimNotifyState_StrikeTrail.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, Blueprintable, const, hidecategories = Object, collapsecategories, meta = (ShowWorldContextPin, DisplayName = "StrikeTrail"))
class ASADAL_API UAnimNotifyState_StrikeTrail : public UAnimNotifyState_Trail
{
	GENERATED_BODY()
	
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag	ActivateGameplayTag = UAsadalGameplayTags::ObjectWeaponTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool			bIsImmediatelyProcessEvent = false;
};
