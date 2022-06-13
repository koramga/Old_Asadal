// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASBTInterface.h"
#include "BehaviorTree/BTTaskNode.h"
#include "UObject/Object.h"
#include "KRGBTTask_Base.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGBTTask_Base : public UBTTaskNode
{
	GENERATED_BODY()

public :
	UKRGBTTask_Base();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

protected:
	bool FillVariablesFromComp(UBehaviorTreeComponent& OwnerComp);
	IKRGGASBTInterface*  GetKRGGASBTInterface() const;
	bool IsFailedExecuteNode(const EBTNodeResult::Type& Type) const;
	
protected:
	TSoftObjectPtr<AAIController>			OwnerAIController;
	TSoftObjectPtr<ACharacter>				OwnerCharacter;
	TSoftObjectPtr<UKRGGASBTComponent>		KRGGASBTComponent;
	TSoftObjectPtr<UBlackboardComponent>	OwnerBlackboardComponent;
	TSoftObjectPtr<UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
	TArray<FName>							BlackboardKeys;
};