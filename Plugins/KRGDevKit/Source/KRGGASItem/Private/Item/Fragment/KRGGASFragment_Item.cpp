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

void UKRGGASFragment_Item::OnActivate(UKRGAbilitySystemComponent* KRGAbilitySystemComponent, bool bIsActivate)
{
	if(true == bIsActivate)
	{
		KRGAbilitySystemComponent->AddLooseGameplayTag(ItemGameplayTag);
	}
	else
	{
		KRGAbilitySystemComponent->RemoveLooseGameplayTag(ItemGameplayTag);
	}
}

bool UKRGGASFragment_Item::CanActivate(UKRGAbilitySystemComponent* KRGAbilitySystemComponent, bool bIsActivate) const
{
	if(IsValid(KRGAbilitySystemComponent))
	{
		return true;
	}

	return false;
}

void UKRGGASFragment_Item::SetActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate)
{
	if(CanActivate(AbilitySystemComponent, bIsActivate))
	{
		OnActivate(AbilitySystemComponent, bIsActivate);
	}
}

bool UKRGGASFragment_Item::HasGameplayTag(const FGameplayTag& GameplayTag)
{
	return ItemGameplayTag.MatchesTag(GameplayTag);
}
