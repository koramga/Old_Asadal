// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "Component/KRGGASBTComponent.h"
#include "KRGBTService_Base.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASBT_API UKRGBTService_Base : public UBTService
{
	GENERATED_BODY()

public :
	UKRGBTService_Base();
	
protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	bool FillVariableFromComp(UBehaviorTreeComponent& OwnerComp);
	bool IsValidBlackboardKeys() const;
	
protected:
	TSoftObjectPtr<AAIController>				OwnerAIController;
	TSoftObjectPtr<ACharacter>					OwnerCharacter;
	TSoftObjectPtr<UKRGGASBTComponent>			KRGGASBTComponent;
	TSoftObjectPtr<UBlackboardComponent>		OwnerBlackboardComponent;
	TSoftObjectPtr<UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
	TArray<FName>								BlackboardKeys;
};
