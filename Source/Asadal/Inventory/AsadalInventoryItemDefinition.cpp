// Fill out your copyright notice in the Description page of Project Settings.


#include "AsadalInventoryItemDefinition.h"

UAsadalInventoryItemDefinition::UAsadalInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
{
}

UAsadalInventoryItemFragment* UAsadalInventoryItemDefinition::FindFragmentByClass(
	TSubclassOf<UAsadalInventoryItemFragment> FragmentClass) const
{
	for(UAsadalInventoryItemFragment* Fragment : Fragments)
	{
		if(Fragment->IsA(FragmentClass))
		{
			return Fragment;
		}
	}
	
	return nullptr;
}
