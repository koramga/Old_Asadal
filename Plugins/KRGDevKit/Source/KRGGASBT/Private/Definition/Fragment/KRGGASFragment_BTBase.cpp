// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTBase.h"

#include "BehaviorTree/BlackboardComponent.h"

bool UKRGGASFragment_BTBase::InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	for(const FName& Key : KeyLists)
	{
		if(FBlackboard::InvalidKey == BlackboardComponent->GetKeyID(Key))
		{
			return false;
		}
	}
	
	return true;
}

bool UKRGGASFragment_BTBase::IsValidBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	for(const FName& Key : KeyLists)
	{
		if(FBlackboard::InvalidKey == BlackboardComponent->GetKeyID(Key))
		{
			return false;
		}
	}
	
	return true;
}
