// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/KRGBTService_Base.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AIController.h"
#include "KRGGASBTInterface.h"
#include "GameFramework/Character.h"
#include "GAS/KRGAbilitySystemComponent.h"

UKRGBTService_Base::UKRGBTService_Base()
{
}

void UKRGBTService_Base::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
}

bool UKRGBTService_Base::FillVariableFromComp(UBehaviorTreeComponent& OwnerComp)
{
	OwnerBlackboardComponent = OwnerComp.GetBlackboardComponent();
	OwnerAIController = OwnerComp.GetAIOwner();

	if(OwnerAIController.IsValid())
	{
		OwnerCharacter = OwnerAIController->GetCharacter();
		
		if(OwnerCharacter.IsValid())
		{
			if(OwnerCharacter->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
			{
				IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OwnerCharacter.Get());

				KRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());
			}
			
			if(OwnerCharacter->GetClass()->ImplementsInterface(UKRGGASBTInterface::StaticClass()))
			{
				IKRGGASBTInterface* KRGGASBTInterface = Cast<IKRGGASBTInterface>(OwnerCharacter.Get());
				
				if(nullptr != KRGGASBTInterface)
				{
					KRGGASBTComponent = KRGGASBTInterface->GetKRGGASBTComponent();
				}
			}
		}
	}

	if(false == OwnerBlackboardComponent.IsValid())
	{
		return false;
	}

	if(false == OwnerCharacter.IsValid())
	{
		return false;
	}

	if(false == KRGGASBTComponent.IsValid())
	{
		return false;
	}

	if(false == OwnerBlackboardComponent.IsValid())
	{
		return false;
	}

	if(false == KRGAbilitySystemComponent.IsValid())
	{
		return false;
	}

	return true;
}

bool UKRGBTService_Base::IsValidBlackboardKeys() const
{
	for(const FName& BlackboardKey : BlackboardKeys)
	{
		if(FBlackboard::InvalidKey == OwnerBlackboardComponent->GetKeyID(BlackboardKey))
		{
			return false;
		}
	}

	return true;
}
