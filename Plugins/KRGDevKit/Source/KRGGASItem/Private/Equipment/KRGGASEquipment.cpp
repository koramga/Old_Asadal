// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/KRGGASEquipment.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"
#include "Equipment/Fragment/KRGGASFragment_Eqipment.h"
#include "Item/KRGGASItem.h"

bool UKRGGASEquipment::AddExtraItem(UKRGGASItem* Item)
{
	if(CanActivateItem(Item))
	{
		ExtraItems.Add(Item);
		return true;
	}

	return false;
}

bool UKRGGASEquipment::SetActivateNextExtraItem()
{
	int32 ExtraItemIndex = ExtraItems.Find(ActivateItem);
	int32 NextExtraIndex = 0;

	if(ExtraItemIndex != INDEX_NONE)
	{
		NextExtraIndex = (ExtraItemIndex + 1) % ExtraItems.Num();
	}

	return SetActivateItem(ExtraItems[NextExtraIndex].Get());
}

bool UKRGGASEquipment::SetActivateItem(UKRGGASItem* Item)
{
	if(CanActivateItem(Item))
	{
		UpdateActivateItem(Item);

		return true;
	}

	return false;
}

FGameplayTag UKRGGASEquipment::GetEquipmentGameplayTag() const
{
	UKRGGASFragment_Eqipment* Equipment = KRGGASDefinition->FindFragment<UKRGGASFragment_Eqipment>();

	if(IsValid(Equipment))
	{
		return Equipment->GetEquipmentGameplayTag();
	}

	return FGameplayTag::EmptyTag;
}

UKRGGASItem* UKRGGASEquipment::GetActivateItem() const
{
	if(ActivateItem.IsValid())
	{
		return ActivateItem.Get();
	}

	return nullptr;
}

bool UKRGGASEquipment::CanActivateItem(UKRGGASItem* Item) const
{
	if(false == KRGGASDefinition.IsValid())
	{
		return false;
	}

	if(false == IsValid(Item))
	{
		return false;
	}
	
	if(false == KRGAbilitySystemComponent.IsValid())
	{
		return false;
	}
	
	FGameplayTagContainer EquipmentGameplayTags = Item->GetEquipmentGameplayTag();

	if(EquipmentGameplayTags.Num() <= 0)
	{
		return false;
	}
	
	UKRGGASFragment_Eqipment* EquipmentFragment = KRGGASDefinition->FindFragment<UKRGGASFragment_Eqipment>();

	if(false == IsValid(EquipmentFragment))
	{
		return false;
	}
	
	if(false == EquipmentGameplayTags.HasTag(EquipmentFragment->GetEquipmentGameplayTag()))
	{
		return false;
	}
	
	if(ActivateItem.IsValid())
	{
		if(false == ActivateItem->CanActivate(KRGAbilitySystemComponent.Get(), false))
		{
			return false;
		}		
	}

	if(IsValid(Item))
	{
		if(false == Item->CanActivate(KRGAbilitySystemComponent.Get(), true))
		{
			return false;
		}
	}

	return true;
}

void UKRGGASEquipment::UpdateActivateItem(UKRGGASItem* Item)
{
	if(ActivateItem.IsValid()
		&& ActivateItem != Item)
	{
		check(ActivateItem->SetActivate(KRGAbilitySystemComponent.Get(), false));
	}

	ActivateItem = Item;

	if(ActivateItem.IsValid())
	{
		check(ActivateItem->SetActivate(KRGAbilitySystemComponent.Get(), true));
	}
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
