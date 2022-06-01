// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/KRGGASDefinition.h"

UKRGGASDefinition::UKRGGASDefinition(const FObjectInitializer& ObjectInitializer)
	: UDataAsset(ObjectInitializer)
{
	
}

UKRGGASFragment* UKRGGASDefinition::FindFragmentByClass(TSubclassOf<UKRGGASFragment> FragmentClass)
{
	for(UKRGGASFragment* Fragment : Fragments)
	{
		if(Fragment->IsA(FragmentClass))
		{
			return Fragment;
		}
	}

	return nullptr;
}
