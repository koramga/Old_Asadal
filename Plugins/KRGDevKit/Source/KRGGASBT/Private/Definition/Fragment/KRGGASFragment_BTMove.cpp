// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

void UKRGGASFragment_BTMove::SetupBlackboard(UBlackboardComponent* BlackboardComponent)
{
	Super::SetupBlackboard(BlackboardComponent);

	UBlackboardData* BlackboardData = BlackboardComponent->GetBlackboardAsset();
	
	if(IsValid(BlackboardData->UpdatePersistentKey<UBlackboardKeyType_Vector>(TEXT("KRGMove"))))
	{
		
	}
	
	BlackboardComponent->SetValueAsVector(TEXT("KRGMove"), FVector(10.f, 10.f, 10.f));

	/*
	FVector MoveVector = BlackboardComponent->GetValueAsVector(TEXT("KRGMove"));
	FVector MoveVector2 = BlackboardComponent->GetValueAsVector(TEXT("KRGMove2"));

	UE_LOG(LogTemp, Display, TEXT("KRGMove : <%s, %s>"), *MoveVector.ToString(), *MoveVector2.ToString());
	*/
}
