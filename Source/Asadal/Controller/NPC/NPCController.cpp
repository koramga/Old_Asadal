// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

//#include "DetourCrowdAIController.h" 생성자 그대로 따름
ANPCController::ANPCController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}

void ANPCController::BeginPlay()
{
	Super::BeginPlay();
}

void ANPCController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCController::OnPossess(APawn* InPawn)
{
	UE_LOG(LogTemp, Display, TEXT("koramga : <%s> OnPossess"), *InPawn->GetName());

	UBlackboardComponent* BlackboardComponent = Blackboard;
	
	if(IsValid(BehaviorTree)
		&& IsValid(BlackboardData))
	{
		if(false == UseBlackboard(BlackboardData, BlackboardComponent))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess UseBlackboard Failed.."));
			return;			
		}
		
		if (false == RunBehaviorTree(BehaviorTree))
		{
			UE_LOG(LogTemp, Display, TEXT("ABaseAIController::OnPossess RunBehaviorTree Failed.."));
			return;
		}

		UE_LOG(LogTemp, Display, TEXT("AI OnPossess Success"));
	}
	
	Super::OnPossess(InPawn);
}

void ANPCController::OnUnPossess()
{
	Super::OnUnPossess();
}
