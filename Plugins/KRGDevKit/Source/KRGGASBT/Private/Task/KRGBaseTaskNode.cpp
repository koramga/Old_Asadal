// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/KRGBaseTaskNode.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UKRGBaseTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Type = Super::ExecuteTask(OwnerComp, NodeMemory);

	if(IsFailedExecuteNode(Type))
	{
		return Type;
	}
	
	OwnerAIController = OwnerComp.GetAIOwner();

	if(false == OwnerAIController.IsValid())
	{
		return EBTNodeResult::Type::Failed;
	}

	OwnerCharacter = OwnerAIController->GetCharacter();

	if(false == OwnerCharacter.IsValid())
	{
		return EBTNodeResult::Type::Failed;
	}

	IKRGGASBTInterface* KRGGASBTInterface = GetKRGGASBTInterface();

	if(nullptr == KRGGASBTInterface)
	{
		return EBTNodeResult::Type::Failed;
	}

	KRGGASBTComponent = KRGGASBTInterface->GetKRGGASBTComponent();
	
	if(false == KRGGASBTComponent.IsValid())
	{
		return EBTNodeResult::Type::Failed;
	}

	OwnerBlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(false == OwnerBlackboardComponent.IsValid())
	{
		return EBTNodeResult::Type::Failed;
	}

	return Type;
}

void UKRGBaseTaskNode::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	OwnerAIController = OwnerComp.GetAIOwner();

	if(false == OwnerAIController.IsValid())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	OwnerCharacter = OwnerAIController->GetCharacter();

	if(false == OwnerCharacter.IsValid())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	IKRGGASBTInterface* KRGGASBTInterface = GetKRGGASBTInterface();

	if(nullptr == KRGGASBTInterface)
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	KRGGASBTComponent = KRGGASBTInterface->GetKRGGASBTComponent();
	
	if(false == KRGGASBTComponent.IsValid())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}

	OwnerBlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(OwnerBlackboardComponent.IsValid())
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}

void UKRGBaseTaskNode::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

IKRGGASBTInterface* UKRGBaseTaskNode::GetKRGGASBTInterface() const
{
	if(OwnerCharacter.IsValid())
	{
		if(OwnerCharacter->GetClass()->ImplementsInterface(UKRGGASBTInterface::StaticClass()))
		{
			return Cast<IKRGGASBTInterface>(OwnerCharacter.Get());
		}
	}

	return nullptr;
}

bool UKRGBaseTaskNode::IsFailedExecuteNode(const EBTNodeResult::Type& Type) const
{
	if(Type == EBTNodeResult::Type::Aborted
		|| Type == EBTNodeResult::Type::Failed)
	{
		return true;
	}

	return false;
}
