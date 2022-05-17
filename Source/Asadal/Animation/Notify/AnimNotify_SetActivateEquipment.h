// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
#include "UObject/Object.h"
#include "AnimNotify_SetActivateEquipment.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UAnimNotify_SetActivateEquipment : public UAnimNotify
{
	GENERATED_BODY()

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag	ActivateGameplayTag = UAsadalGameplayTags::ItemWeaponTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool			bIsActivate = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "bIsActivate", EditConditionHides))
	bool			bIsImmediatelyProcessEvent = true;
};
