// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTTrace.h"

#include "KRGBTBlackboardKeys.h"
#include "KRGMetaToolFunctionLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UKRGGASFragment_BTTrace::UKRGGASFragment_BTTrace()
{
	KeyLists.Empty();
	KeyLists.Add(UKRGBTBlackboardKeys::TraceRangeKey);
	KeyLists.Add(UKRGBTBlackboardKeys::IsFollowTraceTargetKey);
	KeyLists.Add(UKRGBTBlackboardKeys::FollowTraceTargetDeltaRangeKey);
}

bool UKRGGASFragment_BTTrace::InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if(false == Super::InitalizeBlackboardComponent(BlackboardComponent))
	{
		return false;
	}

	TKRGMetaVariable MetaVariable = TraceRange.GetMetaVariable();
	TKRGMetaVariable FollowTraceTargetDeltaRange = TraceTargetDeltaRange.GetMetaVariable();
	BlackboardComponent->SetValueAsFloat(UKRGBTBlackboardKeys::TraceRangeKey, MetaVariable.Get<float>());
	BlackboardComponent->SetValueAsBool(UKRGBTBlackboardKeys::IsFollowTraceTargetKey, bIsFollowTraceTarget);

	if(FollowTraceTargetDeltaRange.IsType<float>())
	{
		BlackboardComponent->SetValueAsFloat(UKRGBTBlackboardKeys::FollowTraceTargetDeltaRangeKey, FollowTraceTargetDeltaRange.Get<float>());
	}
	
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
