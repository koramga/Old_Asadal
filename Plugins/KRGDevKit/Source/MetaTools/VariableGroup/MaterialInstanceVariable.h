// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseVariableMetaDataGroup.h"
#include "MetaTools/Variable/FloatVariableMetaData.h"
#include "MetaTools/Variable/LinearColorVariableMetaData.h"
#include "MetaTools/Variable/VectorVariableMetaData.h"
#include "UObject/Object.h"
#include "MaterialInstanceVariable.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct METATOOLS_API FMaterialInstanceVariable
{
	GENERATED_BODY()

public:
	bool SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	bool SetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent, const TMetaVariable& MetaVariable) const;

	bool SetMaterialInstanceParameterWithBackup(UPrimitiveComponent* PrimitiveComponent);
	bool RollbackMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	
	TMetaVariable GetMaterialInstanceParameter(UPrimitiveComponent* PrimitiveComponent) const;
	TMetaVariable GetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const;

	void StartUpdate();
	bool CanUpdate() const;
	void Update(UPrimitiveComponent* PrimitiveComponent, float DeltaSeconds);
	void EndUpdate();

protected:
	bool SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic) const;
	bool SetMaterialInstanceParameter(UMaterialInstanceDynamic* MaterialInstanceDynamic, const TMetaVariable& MetaVariable) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName						ParameterName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32						DynamicMaterialInstanceElementIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float						LerpTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FBaseVariableMetaDataGroup	StartVariableMetaDataGroup;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "LerpTime > 0.f", EditConditionHides))
	FBaseVariableMetaDataGroup	EndVariableMetaDataGroup;

	bool bIsUpdateLerp = false;
	float LerpDeltaTime = 0.f;	
	TMap<TSoftObjectPtr<UPrimitiveComponent>, TMetaVariable> ResetDynamicMaterialInstanceMetaVariableMap;
};
