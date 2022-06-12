// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/Fragment/KRGGASFragment_BTMove.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UKRGGASFragment_BTMove::UKRGGASFragment_BTMove()
{
	
}

bool UKRGGASFragment_BTMove::InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent)
{
	if(false == Super::InitalizeBlackboardComponent(BlackboardComponent))
	{
		return false;
	}

	return true;

	/*
	UBlackboardData* BlackboardData = BlackboardComponent->GetBlackboardAsset();
 
	UBlackboardKeyType_Vector* BlackboardKeyTypeVecotr = BlackboardData->UpdatePersistentKey<UBlackboardKeyType_Vector>(TEXT("KRGMove"));
	BlackboardData->
	
	if(IsValid(BlackboardKeyTypeVecotr))
	{
		BlackboardComponent->InitializeBlackboard(*BlackboardData);
		
		const uint16 DataOffset = BlackboardKeyTypeVecotr->HasInstance() ? sizeof(FBlackboardInstancedKeyMemory) : 0;
		uint8* RawData = BlackboardComponent->GetKeyRawData(TEXT("KRGMove")) + DataOffset;

		if(RawData)
		{
			UBlackboardKeyType_Vector::SetValue(BlackboardKeyTypeVecotr, RawData, FVector(10.f, 10.f, 10.f));
		}
	}
	*/
	
	//BlackboardComponent->SetValueAsVector(TEXT("KRGMove"), FVector(10.f, 10.f, 10.f));
	//BlackboardComponent->SetValueAsVector(TEXT("KRGTest"), FVector(10.f, 10.f, 10.f));

	/*
	FVector MoveVector = BlackboardComponent->GetValueAsVector(TEXT("KRGMove"));
	FVector MoveVector2 = BlackboardComponent->GetValueAsVector(TEXT("KRGMove2"));

	UE_LOG(LogTemp, Display, TEXT("KRGMove : <%s, %s>"), *MoveVector.ToString(), *MoveVector2.ToString());
	*/
}
