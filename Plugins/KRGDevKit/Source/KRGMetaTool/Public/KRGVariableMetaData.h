// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KRGVariableMetaData.generated.h"

/**
 * 
*/

UENUM(BlueprintType)
enum class EKRGMetaVariableType : uint8
{
	Bool,
	Int,
	Float,
	Vector,
	Vector4,
	LinearColor,
};

UENUM(BlueprintType)
enum class EKRGMetaVariableScope : uint8
{
	Normal,
	Range,
};

typedef TVariant<bool, int32, float, FVector, FVector4, FLinearColor> TKRGMetaVariable;

USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGBaseVariableMetaData();

protected:
	EKRGMetaVariableType	MetaVariableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EKRGMetaVariableScope	MetaVariableScope;

public:
	virtual EKRGMetaVariableType GetMetaVariableType() const;
	virtual EKRGMetaVariableScope GetMetaVariableScope() const;
	virtual TKRGMetaVariable GetMetaVariable() const;
};


USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalBooleanMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeBooleanMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool	Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGBooleanVariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGBooleanVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalBooleanMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeBooleanMetaData	RangeVariableMetaData;

public :
	virtual TKRGMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalFloatMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeFloatMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGFloatVariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGFloatVariableMetaData();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalFloatMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeFloatMetaData	RangeVariableMetaData;

public:
	virtual TKRGMetaVariable GetMetaVariable() const override;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalIntegerMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeIntegerMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGIntegerVariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGIntegerVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalIntegerMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeIntegerMetaData	RangeVariableMetaData;

public :
	virtual TKRGMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalLinearColorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeLinearColorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGLinearColorVariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGLinearColorVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalLinearColorMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeLinearColorMetaData	RangeVariableMetaData;

public :
	virtual TKRGMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalVector4MetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeVector4MetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGVector4VariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGVector4VariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalVector4MetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeVector4MetaData	RangeVariableMetaData;

public :
	virtual TKRGMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGNormalVectorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct KRGMETATOOL_API FKRGRangeVectorMetaData
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Max;
};


USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGVectorVariableMetaData : public FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :	
	FKRGVectorVariableMetaData();

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Normal", EditConditionHides))
	FKRGNormalVectorMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EKRGMetaVariableScope::Range", EditConditionHides))
	FKRGRangeVectorMetaData	RangeVariableMetaData;

public :	
	virtual TKRGMetaVariable GetMetaVariable() const override;
};
