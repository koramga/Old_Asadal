// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/KRGAIDefinition.h"

UKRGAIDefinition::UKRGAIDefinition(const FObjectInitializer& ObjectInitializer)
{
}

UKRGAIFragment* UKRGAIDefinition::FindFragmentByClass(TSubclassOf<UKRGAIFragment> FragmentClass)
{
	for(UKRGAIFragment* Fragment : Fragments)
	{
		if(Fragment->IsA(FragmentClass))
		{
			return Fragment;
		}
	}

	return nullptr;
}
