// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTTrace.h"

#include "KRGGASBTKeys.h"
#include "BehaviorTree/BlackboardComponent.h"

UKRGGASFragment_BTTrace::UKRGGASFragment_BTTrace()
{
	KeyLists.Empty();
	KeyLists.Add(UKRGGASBTKeys::TraceRangeKey);
}

bool UKRGGASFragment_BTTrace::InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if(false == Super::InitalizeBlackboardComponent(BlackboardComponent))
	{
		return false;
	}

	BlackboardComponent->SetValueAsFloat(UKRGGASBTKeys::TraceRangeKey, TraceRange);

	return true;
}

bool UKRGGASFragment_BTTrace::IsValidBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if(false == Super::IsValidBlackboardComponent(BlackboardComponent))
	{
		return false;
	}
	return true;
}
