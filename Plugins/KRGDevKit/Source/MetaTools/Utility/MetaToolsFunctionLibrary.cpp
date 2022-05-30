// Fill out your copyright notice in the Description page of Project Settings.


#include "MetaToolsFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

TMetaVariable UMetaToolsFunctionLibrary::MakeRangeScopeVariable(const TMetaVariable& LMetaVariant, const TMetaVariable& RMetaVariant)
{
	if(LMetaVariant.GetIndex() == static_cast<int>(EMetaVariableType::Bool))
	{
		return LerpVariable(LMetaVariant, RMetaVariant, FMath::Rand() % 2);
	}
	
	return LerpVariable(LMetaVariant, RMetaVariant, FMath::RandRange(0.f, 1.f));
}

TMetaVariable UMetaToolsFunctionLibrary::LerpVariable(const TMetaVariable& LMetaVariant,
	const TMetaVariable& RMetaVariant, float LerpTime)
{
	TMetaVariable Result;

	if (LMetaVariant.GetIndex() == RMetaVariant.GetIndex())
	{
		EMetaVariableType MetaVariableType = static_cast<EMetaVariableType>(LMetaVariant.GetIndex());

		switch (MetaVariableType)
		{
		case EMetaVariableType::Bool:
			if (LMetaVariant.Get<bool>() == RMetaVariant.Get<bool>())
			{
				Result.Set<bool>(LMetaVariant.Get<bool>());
			}
			else
			{
				Result.Set<bool>(static_cast<bool>(LerpTime));
			}
			break;
		case EMetaVariableType::Int:
			Result.Set<int>(FMath::Lerp<int>(LMetaVariant.Get<int>(), RMetaVariant.Get<int>(), LerpTime));
			break;
		case EMetaVariableType::Float:
			Result.Set<float>(FMath::Lerp<float>(LMetaVariant.Get<float>(), RMetaVariant.Get<float>(), LerpTime));
			break;
		case EMetaVariableType::Vector:
			Result.Set<FVector>(FMath::Lerp<FVector>(LMetaVariant.Get<FVector>(), RMetaVariant.Get<FVector>(), LerpTime));
			break;
		case EMetaVariableType::Vector4:
			Result.Set<FVector4>(FMath::Lerp<FVector4>(LMetaVariant.Get<FVector4>(), RMetaVariant.Get<FVector4>(), LerpTime));
			break;
		case EMetaVariableType::LinearColor:
			Result.Set<FLinearColor>(UKismetMathLibrary::LinearColorLerp(LMetaVariant.Get<FLinearColor>(), RMetaVariant.Get<FLinearColor>(), LerpTime));
			break;
		}
	}

	return Result;
}
