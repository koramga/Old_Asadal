// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTTrace.h"

#include "BehaviorTree/BlackboardComponent.h"

void UKRGGASFragment_BTTrace::InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	Super::InitalizeBlackboardComponent(BlackboardComponent);

	if(FBlackboard::InvalidKey != BlackboardComponent->GetKeyID(TEXT("KRGTrace")))
	{
		
	}
}

bool UKRGGASFragment_BTTrace::IsValidBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if(false == Super::IsValidBlackboardComponent(BlackboardComponent))
	{
		return false;
	}
	
	if(FBlackboard::InvalidKey == BlackboardComponent->GetKeyID(TEXT("KRGTrace")))
	{
		return false;
	}

	return true;
}
