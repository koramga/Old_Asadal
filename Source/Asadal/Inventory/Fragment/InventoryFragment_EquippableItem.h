// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InventoryFragment_Item.h"
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
class ASADAL_API UInventoryFragment_EquippableItem : public UInventoryFragment_Item
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEquipmentItemDefinition>						EquipmentItemDefinitions;

protected:
	TArray<TSoftObjectPtr<class ABaseEquipment>>			SpawnEquipmentActors;

protected:
	virtual void OnActivate(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsActivate) override;

public :
	void SetActivateCollisions(bool bIsActivate);
	const TArray<TSoftObjectPtr<class ABaseEquipment>>& GetSpawnEquipmentActors() const;
};
