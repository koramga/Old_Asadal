// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API ANPCController : public AAIController
{
	GENERATED_BODY()

public :
	ANPCController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BehaviorTree")
	class UBehaviorTree*					BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|BehaviorTree")
	class UBlackboardData*					BlackboardData;
};
