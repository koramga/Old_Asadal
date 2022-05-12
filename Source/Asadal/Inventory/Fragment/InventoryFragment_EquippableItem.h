// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Inventory/AsadalInventoryItemDefinition.h"
#include "UObject/Object.h"
#include "InventoryFragment_EquippableItem.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UInventoryFragment_EquippableItem : public UAsadalInventoryItemFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class ABaseEquipment>		BaseEquipmentActorClass;
};
