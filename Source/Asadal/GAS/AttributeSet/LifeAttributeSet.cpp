// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeAttributeSet.h"
#include "GameplayEffectExtension.h"

bool ULifeAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(false == Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	return true;
}

void ULifeAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}
