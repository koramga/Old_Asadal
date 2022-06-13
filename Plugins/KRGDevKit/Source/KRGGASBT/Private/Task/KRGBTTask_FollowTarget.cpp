// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/KRGBTTask_FollowTarget.h"
#include "KRGBTBlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GAS/KRGAbilitySystemComponent.h"

UKRGBTTask_FollowTarget::UKRGBTTask_FollowTarget()
{
	NodeName = TEXT("KRGFollowTarget");
	
	BlackboardKeys.Add(UKRGBTBlackboardKeys::IsFollowTraceTargetKey);
	BlackboardKeys.Add(UKRGBTBlackboardKeys::FollowTraceTargetDeltaRangeKey);
	BlackboardKeys.Add(UKRGBTBlackboardKeys::TraceTargetKey);
}

EBTNodeResult::Type UKRGBTTask_FollowTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type NodeResultType = Super::ExecuteTask(OwnerComp, NodeMemory); 
	
	if(IsFailedExecuteNode(NodeResultType))
	{
		return NodeResultType;
	}

	UKRGAbilitySystemComponent* TargetKRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(OwnerBlackboardComponent->GetValueAsObject(UKRGBTBlackboardKeys::TraceTargetKey));

	if(false == IsValid(TargetKRGAbilitySystemComponent)
		|| false == TargetKRGAbilitySystemComponent->IsActivate())
	{
		return EBTNodeResult::Failed;
	}

	return EBTNodeResult::InProgress;
}

void UKRGBTTask_FollowTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UKRGBTTask_FollowTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
