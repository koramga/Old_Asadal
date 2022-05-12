// Fill out your copyright notice in the Description page of Project Settings.


#include "AsadalInventoryItemDefinition.h"

UAsadalInventoryItemDefinition::UAsadalInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
{
}

const UAsadalInventoryItemFragment* UAsadalInventoryItemDefinition::FindFragmentByClass(
	TSubclassOf<UAsadalInventoryItemFragment> FragmentClass) const
{
	return nullptr;
}
