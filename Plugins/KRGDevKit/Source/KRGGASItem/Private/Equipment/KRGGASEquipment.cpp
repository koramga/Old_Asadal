// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/KRGGASEquipment.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "Equipment/Fragment/KRGGASFragment_Eqipment.h"
#include "Item/KRGGASItem.h"

void UKRGGASEquipment::SetDefinition(UKRGGASDefinition* Definition)
{
	KRGGASDefinition = Definition;
}

void UKRGGASEquipment::SetAbilitySystemComponent(UKRGAbilitySystemComponent* InAbilitySystemComponent)
{
	AbilitySystemComponent = InAbilitySystemComponent;
}

bool UKRGGASEquipment::CanPushItem(UKRGGASItem* Item) const
{
	if(KRGGASDefinition.IsValid()
		&& IsValid(Item))
	{
		UKRGGASFragment_Eqipment* Equipment = KRGGASDefinition->FindFragment<UKRGGASFragment_Eqipment>();

		if(IsValid(Equipment))
		{
			FGameplayTag EquipableGameplayTag = Equipment->GetEquipableGameplayTag();
			
			return Item->GetItemGameplayTag().MatchesTag(EquipableGameplayTag);
		}
	}

	return false;
}

bool UKRGGASEquipment::PushItem(UKRGGASItem* Item)
{
	if(CanPushItem(Item))
	{
		if(false == Items.Contains(Item))
		{
			Items.Add(Item);
			return true;
		}
	}

	return false;
}

bool UKRGGASEquipment::SetActivateItem(UKRGGASItem* Item)
{
	if(false == AbilitySystemComponent.IsValid())
	{
		return false;
	}
	
	if(Items.Contains(Item))
	{
		if(ActivateItem.IsValid()
			&& ActivateItem != Item)
		{
			if(false == ActivateItem->SetActivate(AbilitySystemComponent.Get(), false))
			{
				return false;
			}
		}

		ActivateItem = Item;

		if(ActivateItem.IsValid())
		{
			if(false == ActivateItem->SetActivate(AbilitySystemComponent.Get(), true))
			{
				return false;
			}
		}
	}

	return true;
}
