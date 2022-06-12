// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/Fragment/KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASFragment_BTBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class KRGGASBT_API UKRGGASFragment_BTBase : public UKRGGASFragment
{
	GENERATED_BODY()

public :
	virtual bool InitalizeBlackboardComponent(class UBlackboardComponent* BlackboardComponent);
	virtual bool IsValidBlackboardComponent(class UBlackboardComponent* BlackboardComponent);

protected:
	TArray<FName>							KeyLists;

};
