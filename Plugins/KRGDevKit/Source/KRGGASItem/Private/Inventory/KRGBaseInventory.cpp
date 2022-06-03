// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/KRGBaseInventory.h"

const UKRGGASItemHandle* UKRGBaseInventory::AddItem(UKRGGASDefinition* Definition)
{
	FKRGInventoryItem KRGInventoryItem;

	KRGInventoryItem.KRGGASItemHandle->SetDefinition(Definition);
	
	KRGInventoryItems.Add(KRGInventoryItem);

	return KRGInventoryItem.KRGGASItemHandle.Get();
}

bool UKRGBaseInventory::RemoveItem(const UKRGGASItemHandle* Handle)
{
	int32 Index = 0;
	
	for(FKRGInventoryItem& InventoryItem : KRGInventoryItems)
	{
		if(InventoryItem.KRGGASItemHandle == Handle)
		{
			break;
		}
		
		++Index;
	}

	if(KRGInventoryItems.Num() > Index)
	{
		KRGInventoryItems.RemoveAt(Index);

		return true;
	}

	return false;	
}
