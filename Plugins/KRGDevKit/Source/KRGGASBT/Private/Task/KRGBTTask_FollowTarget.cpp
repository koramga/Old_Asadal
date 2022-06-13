// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/KRGBTTask_FollowTarget.h"

#include "AIController.h"
#include "KRGBTBlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "GAS/KRGAbilitySystemComponent.h"
#include "Kismet/KismetMathLibrary.h"

UKRGBTTask_FollowTarget::UKRGBTTask_FollowTarget()
{
	NodeName = TEXT("KRGFollowTarget");
	bNotifyTick = true;
	
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
	
	bool bIsTraceFollowTarget = OwnerBlackboardComponent->GetValueAsBool(UKRGBTBlackboardKeys::IsFollowTraceTargetKey);

	if(false == bIsTraceFollowTarget)
	{
		return EBTNodeResult::Succeeded;
	}

	float DeltaRange = OwnerBlackboardComponent->GetValueAsFloat(UKRGBTBlackboardKeys::FollowTraceTargetDeltaRangeKey);
	float RemainDistance = GetRemainDistance(TargetKRGAbilitySystemComponent);

	if(RemainDistance <= DeltaRange)
	{
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::InProgress;
}

void UKRGBTTask_FollowTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{	
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	UKRGAbilitySystemComponent* TargetKRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(OwnerBlackboardComponent->GetValueAsObject(UKRGBTBlackboardKeys::TraceTargetKey));

	if(false == IsValid(TargetKRGAbilitySystemComponent)
		|| false == TargetKRGAbilitySystemComponent->IsActivate())
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	
	float DeltaRange = OwnerBlackboardComponent->GetValueAsFloat(UKRGBTBlackboardKeys::FollowTraceTargetDeltaRangeKey);
	float RemainDistance = GetRemainDistance(TargetKRGAbilitySystemComponent);

	if(RemainDistance <= DeltaRange)
	{
		OwnerAIController->StopMovement();
		return FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(OwnerCharacter->GetActorLocation(), TargetKRGAbilitySystemComponent->GetOwner()->GetActorLocation());

		FRotator OwnerActorRotation = OwnerCharacter->GetActorRotation();
		OwnerActorRotation.Yaw = LookAtRotation.Yaw;
		OwnerCharacter->SetActorRotation(OwnerActorRotation);
		
		OwnerAIController->MoveToLocation(TargetKRGAbilitySystemComponent->GetOwner()->GetActorLocation());
	}
}

void UKRGBTTask_FollowTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

float UKRGBTTask_FollowTarget::GetRemainDistance(
	UKRGAbilitySystemComponent* TraceTargetAbilitySystemComponent) const
{
	AActor* TraceTargetActor = TraceTargetAbilitySystemComponent->GetOwner();

	if(false == IsValid(TraceTargetActor))
	{
		return 0.f;
	}

	FVector TraceTargetActorLocation = TraceTargetActor->GetActorLocation();
	FVector OwnerActorLocation = OwnerCharacter->GetActorLocation();

	return FVector::Distance(TraceTargetActorLocation, OwnerActorLocation);
}