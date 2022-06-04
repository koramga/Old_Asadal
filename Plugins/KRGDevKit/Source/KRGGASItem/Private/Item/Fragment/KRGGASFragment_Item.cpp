// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Fragment/KRGGASFragment_Item.h"
#include "GAS/KRGAbilitySystemComponent.h"

const FGameplayTag& UKRGGASFragment_Item::GetItemGameplayTag() const
{
	return ItemGameplayTag;
}

bool UKRGGASFragment_Item::CanCounting() const
{
	return bCanCounting;
}

int32 UKRGGASFragment_Item::GetMaxCount() const
{
	return MaxCount;
}

FName UKRGGASFragment_Item::GetDisplayName() const
{
	return DisplayName;
}

bool UKRGGASFragment_Item::CanActivate(UKRGAbilitySystemComponent* KRGAbilitySystemComponent, bool bIsActivate) const
{
	if(IsValid(KRGAbilitySystemComponent))
	{
		return true;
	}

	return false;
}