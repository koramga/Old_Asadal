// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASFragment_BTBase.h"
#include "KRGVariableMetaData.h"
#include "UObject/Object.h"
#include "KRGGASFragment_BTTrace.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGGASFragment_BTTrace : public UKRGGASFragment_BTBase
{
	GENERATED_BODY()

public :
	UKRGGASFragment_BTTrace();

public :
	virtual bool InitalizeBlackboardComponent(UBlackboardComponent* BlackboardComponent) override;
	virtual bool IsValidBlackboardComponent(UBlackboardComponent* BlackboardComponent) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKRGFloatVariableMetaData	TraceRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool						bIsFollowTraceTarget;
	
	//UPROPERTY(EditAnywhere, BlueprintReadOnly)
	//FKRGFloatVariableMetaData	TraceGoalDelta;
};
