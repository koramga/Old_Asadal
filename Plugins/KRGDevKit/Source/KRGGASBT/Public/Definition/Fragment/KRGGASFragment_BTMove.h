// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASFragment_BTBase.h"
#include "KRGGASFragment_BTMove.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGGASFragment_BTMove : public UKRGGASFragment_BTBase
{
	GENERATED_BODY()

public :
	virtual void SetupBlackboard(UBlackboardComponent* BlackboardComponent) override;
};
