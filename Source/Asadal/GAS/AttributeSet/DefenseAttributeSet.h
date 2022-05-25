// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "Asadal/Asadal.h"
#include "DefenseAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UDefenseAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public :
	UPROPERTY()
	FGameplayAttributeData  BaseResistance;
	ATTRIBUTE_ACCESSORS(UDefenseAttributeSet, BaseResistance);
	
	UPROPERTY()
	FGameplayAttributeData  WaterResistance;
	ATTRIBUTE_ACCESSORS(UDefenseAttributeSet, WaterResistance);

	UPROPERTY()
	FGameplayAttributeData  FireResistance;
	ATTRIBUTE_ACCESSORS(UDefenseAttributeSet, FireResistance);
	
	UPROPERTY()
	FGameplayAttributeData  TreeResistance;
	ATTRIBUTE_ACCESSORS(UDefenseAttributeSet, TreeResistance);	
};
