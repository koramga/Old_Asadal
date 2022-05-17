// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_Item.h"

#include "Asadal/Character/BaseCharacter.h"

void UInventoryFragment_Item::OnActivate(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsActivate)
{
	if(true == bIsActivate)
	{
		BaseCharacter->AddLooseGameplayTag(ItemGameplayTag);
	}
	else
	{
		BaseCharacter->RemoveLooseGameplayTag(ItemGameplayTag);
	}
}

bool UInventoryFragment_Item::CanActivate(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsActivate) const
{
	if(BaseCharacter.IsValid())
	{
		return true;
	}

	return false;
}

void UInventoryFragment_Item::SetActivate(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsActivate)
{
	if(CanActivate(BaseCharacter, bIsActivate))
	{
		OnActivate(BaseCharacter, bIsActivate);
	}
}

bool UInventoryFragment_Item::HasGameplayTag(const FGameplayTag& GameplayTag)
{
	return ItemGameplayTag.MatchesTag(GameplayTag);
}

const FGameplayTag& UInventoryFragment_Item::GetItemGameplayTag() const
{
	return ItemGameplayTag;
}