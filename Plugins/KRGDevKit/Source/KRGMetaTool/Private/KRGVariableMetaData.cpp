// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGVariableMetaData.h"
#include "KRGMetaToolFunctionLibrary.h"

FKRGBaseVariableMetaData::FKRGBaseVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Bool;
	MetaVariableScope = EKRGMetaVariableScope::Normal;
}

EKRGMetaVariableType FKRGBaseVariableMetaData::GetMetaVariableType() const
{
	return MetaVariableType;
}

EKRGMetaVariableScope FKRGBaseVariableMetaData::GetMetaVariableScope() const
{
	return MetaVariableScope;
}

TKRGMetaVariable FKRGBaseVariableMetaData::GetMetaVariable() const
{
	return TKRGMetaVariable();
}

FKRGBooleanVariableMetaData::FKRGBooleanVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Bool;
}

TKRGMetaVariable FKRGBooleanVariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<bool>(NormalVariableMetaData.Value);
	}
	else if (EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;

		MinMetaVariable.Set<bool>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<bool>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}

FKRGFloatVariableMetaData::FKRGFloatVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Float;
}

TKRGMetaVariable FKRGFloatVariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<float>(NormalVariableMetaData.Value);
	}
	else if (EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;

		MinMetaVariable.Set<float>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<float>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}

FKRGIntegerVariableMetaData::FKRGIntegerVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Int;
}

TKRGMetaVariable FKRGIntegerVariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<int>(NormalVariableMetaData.Value);
	}
	else if(EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<int>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<int>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}


FKRGLinearColorVariableMetaData::FKRGLinearColorVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::LinearColor;
}

TKRGMetaVariable FKRGLinearColorVariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FLinearColor>(NormalVariableMetaData.Value);
	}
	else if(EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FLinearColor>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FLinearColor>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}

FKRGVector4VariableMetaData::FKRGVector4VariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Vector4;
}

TKRGMetaVariable FKRGVector4VariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FVector4>(NormalVariableMetaData.Value);
	}
	else if(EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FVector4>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FVector4>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}

FKRGVectorVariableMetaData::FKRGVectorVariableMetaData()
{
	MetaVariableType = EKRGMetaVariableType::Vector;
}

TKRGMetaVariable FKRGVectorVariableMetaData::GetMetaVariable() const
{
	TKRGMetaVariable MetaVariable;

	if (EKRGMetaVariableScope::Normal == MetaVariableScope)
	{
		MetaVariable.Set<FVector>(NormalVariableMetaData.Value);
	}
	else if(EKRGMetaVariableScope::Range == MetaVariableScope)
	{
		TKRGMetaVariable MinMetaVariable;
		TKRGMetaVariable MaxMetaVariable;
		
		MinMetaVariable.Set<FVector>(RangeVariableMetaData.Min);
		MaxMetaVariable.Set<FVector>(RangeVariableMetaData.Max);

		MetaVariable = UKRGMetaToolFunctionLibrary::MakeRangeScopeVariable(MinMetaVariable, MaxMetaVariable);
	}

	return MetaVariable;
}