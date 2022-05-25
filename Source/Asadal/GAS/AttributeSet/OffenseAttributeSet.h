// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Asadal/Asadal.h"
#include "OffenseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UOffenseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
	UPROPERTY()
	FGameplayAttributeData  BaseDamageBuff;
	ATTRIBUTE_ACCESSORS(UOffenseAttributeSet, BaseDamageBuff);
	
	UPROPERTY()
	FGameplayAttributeData  WaterDamageBuff;
	ATTRIBUTE_ACCESSORS(UOffenseAttributeSet, WaterDamageBuff);

	UPROPERTY()
	FGameplayAttributeData  FireDamageBuff;
	ATTRIBUTE_ACCESSORS(UOffenseAttributeSet, FireDamageBuff);
	
	UPROPERTY()
	FGameplayAttributeData  TreeDamageBuff;
	ATTRIBUTE_ACCESSORS(UOffenseAttributeSet, TreeDamageBuff);

	UPROPERTY()
	FGameplayAttributeData	CriticalRate;
	ATTRIBUTE_ACCESSORS(UOffenseAttributeSet, CriticalRate);
};
