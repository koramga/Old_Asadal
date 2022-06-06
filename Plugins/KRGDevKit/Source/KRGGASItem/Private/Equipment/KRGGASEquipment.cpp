// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/KRGGASEquipment.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "Equipment/Fragment/KRGGASFragment_Eqipment.h"
#include "Item/KRGGASItem.h"

bool UKRGGASEquipment::CanPushItem(UKRGGASItem* Item) const
{
	if(KRGGASDefinition.IsValid()
		&& IsValid(Item))
	{
		FGameplayTagContainer EquipmentGameplayTags = Item->GetEquipmentGameplayTag();

		if(EquipmentGameplayTags.Num() > 0)
		{
			UKRGGASFragment_Eqipment* Equipment = KRGGASDefinition->FindFragment<UKRGGASFragment_Eqipment>();

			if(IsValid(Equipment))
			{
				return EquipmentGameplayTags.HasTag(Equipment->GetEquipmentGameplayTag());
			}			
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
	if(false == KRGAbilitySystemComponent.IsValid())
	{
		return false;
	}
	
	if(Items.Contains(Item))
	{
		if(ActivateItem.IsValid()
			&& ActivateItem != Item)
		{
			if(false == ActivateItem->SetActivate(KRGAbilitySystemComponent.Get(), false))
			{
				return false;
			}
		}

		ActivateItem = Item;

		if(ActivateItem.IsValid())
		{
			if(false == ActivateItem->SetActivate(KRGAbilitySystemComponent.Get(), true))
			{
				return false;
			}
		}
	}

	return true;
}

bool UKRGGASEquipment::CanUpdateDefinition(UKRGGASDefinition* Definition) const
{
	if(false == Super::CanUpdateDefinition(Definition))
	{
		return false;
	}

	if(false == HasFragment<UKRGGASFragment_Eqipment>(Definition))
	{
		return false;
	}

	return true;
}
