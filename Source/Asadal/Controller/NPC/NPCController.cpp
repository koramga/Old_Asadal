// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "Navigation/CrowdFollowingComponent.h"

//#include "DetourCrowdAIController.h" 생성자 그대로 따름
ANPCController::ANPCController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>(TEXT("PathFollowingComponent")))
{
}