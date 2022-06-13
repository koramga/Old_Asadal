// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGMetaToolFunctionLibrary.h"

#include "Kismet/KismetMathLibrary.h"

TKRGMetaVariable UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(const TKRGMetaVariable& LMetaVariant,
                                                                     const TKRGMetaVariable& RMetaVariant)
{
	if(LMetaVariant.GetIndex() == static_cast<int>(EKRGMetaVariableType::Bool))
	{
		return LerpVariable(LMetaVariant, RMetaVariant, FMath::Rand() % 2);
	}
	
	return LerpVariable(LMetaVariant, RMetaVariant, FMath::RandRange(0.f, 1.f));
}

TKRGMetaVariable UKRGMetaToolFunctionLibrary::LerpVariable(const TKRGMetaVariable& LMetaVariant,
	const TKRGMetaVariable& RMetaVariant, float LerpTime)
{
	TKRGMetaVariable Result;

	if (LMetaVariant.GetIndex() == RMetaVariant.GetIndex())
	{
		EKRGMetaVariableType MetaVariableType = static_cast<EKRGMetaVariableType>(LMetaVariant.GetIndex());

		switch (MetaVariableType)
		{
		case EKRGMetaVariableType::Bool:
			if (LMetaVariant.Get<bool>() == RMetaVariant.Get<bool>())
			{
				Result.Set<bool>(LMetaVariant.Get<bool>());
			}
			else
			{
				Result.Set<bool>(static_cast<bool>(LerpTime));
			}
			break;
		case EKRGMetaVariableType::Int:
			Result.Set<int>(FMath::Lerp<int>(LMetaVariant.Get<int>(), RMetaVariant.Get<int>(), LerpTime));
			break;
		case EKRGMetaVariableType::Float:
			Result.Set<float>(FMath::Lerp<float>(LMetaVariant.Get<float>(), RMetaVariant.Get<float>(), LerpTime));
			break;
		case EKRGMetaVariableType::Vector:
			Result.Set<FVector>(FMath::Lerp<FVector>(LMetaVariant.Get<FVector>(), RMetaVariant.Get<FVector>(), LerpTime));
			break;
		case EKRGMetaVariableType::Vector4:
			Result.Set<FVector4>(FMath::Lerp<FVector4>(LMetaVariant.Get<FVector4>(), RMetaVariant.Get<FVector4>(), LerpTime));
			break;
		case EKRGMetaVariableType::LinearColor:
			Result.Set<FLinearColor>(UKismetMathLibrary::LinearColorLerp(LMetaVariant.Get<FLinearColor>(), RMetaVariant.Get<FLinearColor>(), LerpTime));
			break;
		}
	}

	return Result;
}

bool UKRGMetaToolFunctionLibrary::IsMatchedVariableType(const TKRGMetaVariable& MetaVariable,
	EKRGMetaVariableType MetaVariableType)
{
	EKRGMetaVariableType InMetaVariableType = static_cast<EKRGMetaVariableType>(MetaVariable.GetIndex());

	if(MetaVariableType == InMetaVariableType)
	{
		return true;
	}

	return false;
}
