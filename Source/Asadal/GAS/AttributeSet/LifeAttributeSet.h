// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Asadal/Asadal.h"
#include "LifeAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API ULifeAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
public :
	//Attributes for Health
	UPROPERTY()
	FGameplayAttributeData  Health;
	ATTRIBUTE_ACCESSORS(ULifeAttributeSet, Health);

	UPROPERTY()
	FGameplayAttributeData  MaxHealth;
	ATTRIBUTE_ACCESSORS(ULifeAttributeSet, MaxHealth);

	//Attributes for Mana
	UPROPERTY()
	FGameplayAttributeData  Mana;
	ATTRIBUTE_ACCESSORS(ULifeAttributeSet, Mana);

	UPROPERTY()
	FGameplayAttributeData  MaxMana;
	ATTRIBUTE_ACCESSORS(ULifeAttributeSet, MaxMana);
	
	UPROPERTY()
	FGameplayAttributeData  Shield;
	ATTRIBUTE_ACCESSORS(ULifeAttributeSet, Shield);
};
