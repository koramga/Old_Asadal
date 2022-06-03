// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/Handle/KRGGASItemHandle.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "Item/KRGGASItem.h"

void UKRGGASItemHandle::SetDefinition(UKRGGASDefinition* Definition)
{
	if(false == KRGGASItem.IsValid())
	{
		KRGGASItem = NewObject<UKRGGASItem>();
	}

	KRGGASItem->SetDefinition(Definition);
}

const TSoftObjectPtr<UKRGGASItem>& UKRGGASItemHandle::GetItem() const
{
	return KRGGASItem;
}
