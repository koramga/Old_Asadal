// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGVariable.h"

#include "KRGMetaToolFunctionLibrary.h"

FKRGBaseVariableMetaDataGroup::FKRGBaseVariableMetaDataGroup()
{
	
}

TKRGMetaVariable FKRGBaseVariableMetaDataGroup::GetMetaVariable() const
{
	switch (MetaVariableType)
	{
	case EKRGMetaVariableType::Bool :
		return BoolVariableMetaData.GetMetaVariable();
	case EKRGMetaVariableType::Float :
		return FloatVariableMetaData.GetMetaVariable();
	case EKRGMetaVariableType::Int :
		return IntVariableMetaData.GetMetaVariable();
	case EKRGMetaVariableType::Vector :
		return VectorVariableMetaData.GetMetaVariable();
	case EKRGMetaVariableType::Vector4 :
		return Vector4VariableMetaData.GetMetaVariable();
	case EKRGMetaVariableType::LinearColor :
		return LinearColorVariableMetaData.GetMetaVariable();
	}

	return TKRGMetaVariable();
}

EKRGMetaVariableType FKRGBaseVariableMetaDataGroup::GetMetaVariableType() const
{
	return MetaVariableType;
}

bool FKRGMaterialInstanceVariable::SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return SetMaterialInstanceParameter(MaterialInstanceDynamic);
	}

	return false;
}

bool FKRGMaterialInstanceVariable::SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent,
	const TKRGMetaVariable& MetaVariable) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return SetMaterialInstanceParameter(MaterialInstanceDynamic, MetaVariable);
	}

	return false;
}

bool FKRGMaterialInstanceVariable::SetMaterialInstanceParameterWithBackup(UPrimitiveComponent* PrimitiveComponent)
{
	TKRGMetaVariable NewMetaVariable = GetMaterialInstanceParameter(PrimitiveComponent);
	
	ResetDynamicMaterialInstanceMetaVariableMap.Remove(PrimitiveComponent);
	ResetDynamicMaterialInstanceMetaVariableMap.Add(PrimitiveComponent, NewMetaVariable);

	return SetMaterialInstanceParameter(PrimitiveComponent);
}

bool FKRGMaterialInstanceVariable::RollbackMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const
{
	if(ResetDynamicMaterialInstanceMetaVariableMap.Contains(PrimitiveComponent))
	{
		TKRGMetaVariable MetaVariable = ResetDynamicMaterialInstanceMetaVariableMap.FindRef(PrimitiveComponent);

		return SetMaterialInstanceParameter(PrimitiveComponent, MetaVariable);
	}
	
	return false;
}

bool FKRGMaterialInstanceVariable::SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const
{
	TKRGMetaVariable MetaVariable = StartVariableMetaDataGroup.GetMetaVariable();
	
	return SetMaterialInstanceParameter(MaterialInstanceDynamic, MetaVariable);

	/*
	if(IsValid(MaterialInstanceDynamic))
	{
		TMetaVariable MetaVariable = BaseVariableMetaDataGroup.GetMetaVariable();
		EMetaVariableType MetaVariableType = BaseVariableMetaDataGroup.GetMetaVariableType();

		switch (MetaVariableType)
		{
		case EMetaVariableType::Bool:
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<bool>());
			break;

		case EMetaVariableType::Float :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<float>());
			break;

		case EMetaVariableType::Int :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<int>());
			break;

		case EMetaVariableType::Vector :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FVector>());
			break;

		case EMetaVariableType::Vector4 :
			{
				FVector4 Vector4  = MetaVariable.Get<FVector4>();
				FLinearColor LinearColor;
				LinearColor.R = Vector4.X;
				LinearColor.G = Vector4.Y;
				LinearColor.B = Vector4.Z;
				LinearColor.A = Vector4.W;

				MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, LinearColor);
			}
			break;

		case EMetaVariableType::LinearColor :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FLinearColor>());
			break;
		}

		return true;
	}
	
	return false;
	*/	
}

bool FKRGMaterialInstanceVariable::SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic,
	const TKRGMetaVariable& MetaVariable) const
{
	if(IsValid(MaterialInstanceDynamic))
	{
		EKRGMetaVariableType MetaVariableType = static_cast<EKRGMetaVariableType>(MetaVariable.GetIndex());

		switch (MetaVariableType)
		{
		case EKRGMetaVariableType::Bool:
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<bool>());
			break;

		case EKRGMetaVariableType::Float :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<float>());
			break;

		case EKRGMetaVariableType::Int :
			MaterialInstanceDynamic->SetScalarParameterValue(ParameterName, MetaVariable.Get<int>());
			break;

		case EKRGMetaVariableType::Vector :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FVector>());
			break;

		case EKRGMetaVariableType::Vector4 :
			{
				FVector4 Vector4  = MetaVariable.Get<FVector4>();
				FLinearColor LinearColor;
				LinearColor.R = Vector4.X;
				LinearColor.G = Vector4.Y;
				LinearColor.B = Vector4.Z;
				LinearColor.A = Vector4.W;

				MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, LinearColor);
			}
			break;

		case EKRGMetaVariableType::LinearColor :
			MaterialInstanceDynamic->SetVectorParameterValue(ParameterName, MetaVariable.Get<FLinearColor>());
			break;
		}

		return true;
	}
	
	return false;
}

TKRGMetaVariable FKRGMaterialInstanceVariable::GetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const
{
	UMaterialInstanceDynamic* MaterialInstanceDynamic = PrimitiveComponent->CreateDynamicMaterialInstance(DynamicMaterialInstanceElementIndex);

	if(IsValid(MaterialInstanceDynamic))
	{
		return GetMaterialInstanceParameter(MaterialInstanceDynamic);
	}

	return TKRGMetaVariable();
}

TKRGMetaVariable FKRGMaterialInstanceVariable::GetMaterialInstanceParameter(
	UMaterialInstanceDynamic* MaterialInstanceDynamic) const
{
	TKRGMetaVariable ReturnMetaVariable = TKRGMetaVariable();
	EKRGMetaVariableType MetaVariableType = StartVariableMetaDataGroup.GetMetaVariableType();

	float Sclar;
	FVector Vector;
	FLinearColor LinearColor;
	FVector4 Vector4;
	
	switch (MetaVariableType)
	{
	case EKRGMetaVariableType::Bool:
	case EKRGMetaVariableType::Float :
	case EKRGMetaVariableType::Int :
		MaterialInstanceDynamic->GetScalarParameterValue(ParameterName, Sclar);
		ReturnMetaVariable.Set<float>(Sclar);
		break;

	case EKRGMetaVariableType::Vector :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);

		Vector.X = LinearColor.R;
		Vector.Y = LinearColor.G;
		Vector.Z = LinearColor.B;
		
		ReturnMetaVariable.Set<FVector>(Vector);
		break;

	case EKRGMetaVariableType::Vector4 :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);

		Vector4.X = LinearColor.R;
		Vector4.Y = LinearColor.G;
		Vector4.Z = LinearColor.B;
		Vector4.W = LinearColor.A;
		
		ReturnMetaVariable.Set<FVector4>(Vector4);
		break;
		
	case EKRGMetaVariableType::LinearColor :
		MaterialInstanceDynamic->GetVectorParameterValue(ParameterName, LinearColor);
		ReturnMetaVariable.Set<FLinearColor>(LinearColor);
		break;
	}

	return ReturnMetaVariable;
}

void FKRGMaterialInstanceVariable::StartUpdate()
{
	bIsUpdateLerp = true;
	LerpDeltaTime = 0.f;
}

bool FKRGMaterialInstanceVariable::CanUpdate() const
{
	if(LerpTime <= 0.f)
	{
		return false;
	}
	
	if(StartVariableMetaDataGroup.GetMetaVariableType() != EndVariableMetaDataGroup.GetMetaVariableType())
	{
		return false;
	}

	return bIsUpdateLerp;
}

void FKRGMaterialInstanceVariable::Update(UPrimitiveComponent* PrimitiveComponent, float DeltaSeconds)
{
	if(CanUpdate())
	{
		LerpDeltaTime += DeltaSeconds;

		if(LerpDeltaTime > LerpTime)
		{
			EndUpdate();
		}
		else
		{
			float ClampDeltaTime = FMath::Clamp(LerpDeltaTime / LerpTime, 0.f, 1.f);

			const TKRGMetaVariable StartMetaVariable = StartVariableMetaDataGroup.GetMetaVariable();
			const TKRGMetaVariable EndMetaVariable = EndVariableMetaDataGroup.GetMetaVariable();

			const TKRGMetaVariable UpdateMetaVariable = UKRGMetaToolFunctionLibrary::LerpVariable(StartMetaVariable, EndMetaVariable, ClampDeltaTime);

			SetMaterialInstanceParameter(PrimitiveComponent, UpdateMetaVariable);
		}
	}
}

void FKRGMaterialInstanceVariable::EndUpdate()
{
	bIsUpdateLerp = false;
}