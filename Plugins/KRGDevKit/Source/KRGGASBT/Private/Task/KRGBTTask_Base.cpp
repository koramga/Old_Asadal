// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/KRGBTTask_Base.h"

#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/KRGAbilitySystemComponent.h"

UKRGBTTask_Base::UKRGBTTask_Base()
{
}

EBTNodeResult::Type UKRGBTTask_Base::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Type = Super::ExecuteTask(OwnerComp, NodeMemory);

	if(IsFailedExecuteNode(Type))
	{
		return Type;
	}
	
	if(false == FillVariablesFromComp(OwnerComp))
	{
		return EBTNodeResult::Type::Failed;		
	}

	for(const FName& BlackboardKey : BlackboardKeys)
	{
		if(FBlackboard::InvalidKey == OwnerBlackboardComponent->GetKeyID(BlackboardKey))
		{
			return EBTNodeResult::Type::Failed;
		}
	}
	
	return Type;
}

void UKRGBTTask_Base::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if(false == FillVariablesFromComp(OwnerComp))
	{
		return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);		
	}

	for(const FName& BlackboardKey : BlackboardKeys)
	{
		if(FBlackboard::InvalidKey == OwnerBlackboardComponent->GetKeyID(BlackboardKey))
		{
			return FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		}
	}
	
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UKRGBTTask_Base::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}

bool UKRGBTTask_Base::FillVariablesFromComp(UBehaviorTreeComponent& OwnerComp)
{
	
	OwnerAIController = OwnerComp.GetAIOwner();

	if(false == OwnerAIController.IsValid())
	{
		return false;
	}

	OwnerCharacter = OwnerAIController->GetCharacter();

	if(false == OwnerCharacter.IsValid())
	{
		return false;
	}

	IKRGGASBTInterface* KRGGASBTInterface = GetKRGGASBTInterface();

	if(nullptr == KRGGASBTInterface)
	{
		return false;
	}

	KRGGASBTComponent = KRGGASBTInterface->GetKRGGASBTComponent();
	
	if(false == KRGGASBTComponent.IsValid())
	{
		return false;
	}

	OwnerBlackboardComponent = OwnerComp.GetBlackboardComponent();

	if(false == OwnerBlackboardComponent.IsValid())
	{
		return false;
	}
	
	if(OwnerCharacter->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
	{
		IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerCharacter.Get());

		KRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());
	}

	if(false == KRGAbilitySystemComponent.IsValid())
	{
		return false;
	}

	return true;
}

IKRGGASBTInterface* UKRGBTTask_Base::GetKRGGASBTInterface() const
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

bool UKRGBTTask_Base::IsFailedExecuteNode(const EBTNodeResult::Type& Type) const
{
	if(Type == EBTNodeResult::Type::Aborted
		|| Type == EBTNodeResult::Type::Failed)
	{
		return true;
	}

	return false;
}
