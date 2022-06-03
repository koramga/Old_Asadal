// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGGASDefinition.h"
#include "Handle/KRGGASItemHandle.h"
#include "UObject/Object.h"
#include "KRGBaseInventory.generated.h"

/**
 * 
 */

USTRUCT()
struct FKRGInventoryItem
{
	GENERATED_BODY()

	TSoftObjectPtr<UKRGGASItemHandle>	KRGGASItemHandle;
};

UCLASS()
class KRGGASITEM_API UKRGBaseInventory : public UObject
{
	GENERATED_BODY()

public :
	const UKRGGASItemHandle* AddItem(UKRGGASDefinition* Definition);
	bool RemoveItem(const UKRGGASItemHandle* Handle);

protected:
	TArray<FKRGInventoryItem>		KRGInventoryItems;
};
