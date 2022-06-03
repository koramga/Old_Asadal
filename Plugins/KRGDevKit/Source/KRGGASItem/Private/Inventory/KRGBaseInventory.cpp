// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/KRGBaseInventory.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "Item/KRGGASItem.h"

void UKRGBaseInventory::SetAbilitySystemComponent(UKRGAbilitySystemComponent* InKRGAbilitySystemComponent)
{
	KRGAbilitySystemComponent = InKRGAbilitySystemComponent;
}

const UKRGGASItemHandle* UKRGBaseInventory::AddItem(UKRGGASDefinition* Definition)
{
	FKRGInventoryItem KRGInventoryItem;

	KRGInventoryItem.KRGGASItemHandle->SetDefinition(Definition);
	
	KRGInventoryItems.Add(KRGInventoryItem);

	return KRGInventoryItem.KRGGASItemHandle.Get();
}

bool UKRGBaseInventory::ActivateItem(const UKRGGASItemHandle* Handle, bool bIsActivate)
{
	int32 Index = FindIndexFromHandle(Handle);

	if(Index >= 0)
	{
		return Handle->GetItem()->SetActivate(KRGAbilitySystemComponent.Get(), bIsActivate);
	}

	return false;
}

bool UKRGBaseInventory::RemoveItem(const UKRGGASItemHandle* Handle)
{
	if(true == Handle->GetItem()->IsActivate())
	{
		return false;
	}

	int32 Index = FindIndexFromHandle(Handle);

	if(Index >= 0
		&& KRGInventoryItems.Num() > Index)
	{
		KRGInventoryItems.RemoveAt(Index);

		return true;
	}

	return false;	
}

int32 UKRGBaseInventory::FindIndexFromHandle(const UKRGGASItemHandle* Handle)
{
	int32 Index = 0;
	
	for(FKRGInventoryItem& InventoryItem : KRGInventoryItems)
	{
		if(InventoryItem.KRGGASItemHandle == Handle)
		{
			return Index;
		}
		
		++Index;
	}

	return -1;
}
