// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGBTService_Base.h"
#include "UObject/Object.h"
#include "KRGBTService_DetectTarget.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGBTService_DetectTarget : public UKRGBTService_Base
{
	GENERATED_BODY()

public :
	UKRGBTService_DetectTarget();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
