// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Asadal/Asadal.h"
#include "GAS/AttributeSet/KRGAttributeSet.h"
#include "BaseCharacterAttributeSet.generated.h"



/**
 * 
 */
UCLASS()
class ASADAL_API UBaseCharacterAttributeSet : public UKRGAttributeSet
{
	GENERATED_BODY()

public :
	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
public :
	//Attributes for Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
	FGameplayAttributeData  Health;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Health);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
	FGameplayAttributeData  MaxHealth;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, MaxHealth);

	//Attributes for Mana
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
	FGameplayAttributeData  Mana;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, Mana);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BaseAttribute")
	FGameplayAttributeData  MaxMana;
	ATTRIBUTE_ACCESSORS(UBaseCharacterAttributeSet, MaxMana);


	
};
