// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGVariableMetaData.h"
#include "KRGVariable.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGBaseVariableMetaDataGroup
{
	GENERATED_BODY()

public :
	FKRGBaseVariableMetaDataGroup();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EKRGMetaVariableType	MetaVariableType = EKRGMetaVariableType::Float;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::Bool", EditConditionHides))
	FKRGBooleanVariableMetaData		BoolVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::Int", EditConditionHides))
	FKRGIntegerVariableMetaData		IntVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::Float", EditConditionHides))
	FKRGFloatVariableMetaData			FloatVariableMetaData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::Vector", EditConditionHides))
	FKRGVectorVariableMetaData			VectorVariableMetaData;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::Vector4", EditConditionHides))
	FKRGVector4VariableMetaData		Vector4VariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableType == EKRGMetaVariableType::LinearColor", EditConditionHides))
	FKRGLinearColorVariableMetaData	LinearColorVariableMetaData;

public :
	virtual TKRGMetaVariable GetMetaVariable() const;
	EKRGMetaVariableType GetMetaVariableType() const;
};

USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGMaterialInstanceVariable
{
	GENERATED_BODY()

public:
	bool SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	bool SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent, const TKRGMetaVariable& MetaVariable) const;

	bool SetMaterialInstanceParameterWithBackup(UPrimitiveComponent* PrimitiveComponent);
	bool RollbackMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	
	TKRGMetaVariable GetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	TKRGMetaVariable GetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const;

	void StartUpdate();
	bool CanUpdate() const;
	void Update(UPrimitiveComponent* PrimitiveComponent, float DeltaSeconds);
	void EndUpdate();

protected:
	bool SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const;
	bool SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic, const TKRGMetaVariable& MetaVariable) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName						ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32						DynamicMaterialInstanceElementIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float						LerpTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FKRGBaseVariableMetaDataGroup	StartVariableMetaDataGroup;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LerpTime > 0.f", EditConditionHides))
	FKRGBaseVariableMetaDataGroup	EndVariableMetaDataGroup;

	bool bIsUpdateLerp = false;
	float LerpDeltaTime = 0.f;	
	TMap<TSoftObjectPtr<UPrimitiveComponent>, TKRGMetaVariable> ResetDynamicMaterialInstanceMetaVariableMap;
};
