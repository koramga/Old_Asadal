// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseCharacterAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public :
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
