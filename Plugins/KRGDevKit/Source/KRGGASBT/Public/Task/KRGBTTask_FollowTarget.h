// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Task/KRGBTTask_Base.h"
#include "UObject/Object.h"
#include "KRGBTTask_FollowTarget.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGBTTask_FollowTarget : public UKRGBTTask_Base
{
	GENERATED_BODY()

public :
	UKRGBTTask_FollowTarget();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

protected:
	float	GetRemainDistance(class UKRGAbilitySystemComponent* TraceTargetAbilitySystemComponent) const;
};
