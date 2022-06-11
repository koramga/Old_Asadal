// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/KRGTraceNode.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UKRGTraceNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Type = Super::ExecuteTask(OwnerComp, NodeMemory);

	if(IsFailedExecuteNode(Type))
	{
		return Type;
	}

	UKRGGASFragment_BTMove* MoveFragment = KRGGASBTComponent->GetMoveFragment();

	if(IsValid(MoveFragment))
	{
		FVector MoveVector = OwnerBlackboardComponent->GetValueAsVector(TEXT("KRGMove"));
		FVector TestVector  = OwnerBlackboardComponent->GetValueAsVector(TEXT("KRGTest"));

		UE_LOG(LogTemp, Display, TEXT("TraceNode : <%s, %s>"), *MoveVector.ToString(), *TestVector.ToString());
	}

	return EBTNodeResult::Failed;
}

void UKRGTraceNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UKRGTraceNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
