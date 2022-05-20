// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "Asadal/Character/BaseCharacter.h"

bool UBaseCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if(false == Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	//if(Data.EvaluatedData.Attribute == GetHealthAttribute())
	//{
	//	if(Data.EvaluatedData.Magnitude < 0.f)
	//	{
	//		//음수기때문에 Damage일 확률이 높다. 그러므로
	//		ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(GetOwningActor());
	//
	//		if(IsValid(BaseCharacter))
	//		{
	//			if(BaseCharacter->IsGodMode())
	//			{
	//				Data.EvaluatedData.Magnitude = 0.f;
	//			}
	//		}
	//	}
	//}

	return true;
}

void UBaseCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
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
