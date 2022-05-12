// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Asadal/Inventory/AsadalInventoryItemDefinition.h"
#include "UObject/Object.h"
#include "InventoryFragment_EquippableItem.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FEquipmentItemDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABaseEquipment>		BaseEquipmentActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName									AttachBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform								Transform;
};

UCLASS()
class ASADAL_API UInventoryFragment_EquippableItem : public UAsadalInventoryItemFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag											EquipmentGameplayTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEquipmentItemDefinition>						EquipmentItemDefinitions;

protected:
	TArray<TSoftObjectPtr<class ABaseEquipment>>			SpawnEquipmentActors;

public :
	void SetEquip(TSoftObjectPtr<class ABaseCharacter> BaseCharacter, bool bIsEquip);
	bool HasGameplayTag(FGameplayTag GameplayTag);
	void SetActivateCollisions(bool bIsActivate);
	FGameplayTag GetEquipmentGameplayTag() const;
	const TArray<TSoftObjectPtr<class ABaseEquipment>>& GetSpawnEquipmentActors() const;
};
