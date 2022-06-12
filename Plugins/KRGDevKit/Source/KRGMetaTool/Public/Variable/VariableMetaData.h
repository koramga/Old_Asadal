// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VariableMetaData.generated.h"

/**
 * 
*/

UENUM(BlueprintType)
enum class EMetaVariableType : uint8
{
	Bool,
	Int,
	Float,
	Vector,
	Vector4,
	LinearColor,
};

UENUM(BlueprintType)
enum class EMetaVariableScope : uint8
{
	Normal,
	Range,
};

typedef TVariant<bool, int32, float, FVector, FVector4, FLinearColor> TMetaVariable;

USTRUCT(BlueprintType)
struct KRGMETATOOL_API FKRGBaseVariableMetaData
{
	GENERATED_BODY()

public :
	FKRGBaseVariableMetaData();

protected:
	EMetaVariableType	MetaVariableType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EMetaVariableScope	MetaVariableScope;

public:
	virtual EMetaVariableType GetMetaVariableType() const;
	virtual EMetaVariableScope GetMetaVariableScope() const;
	virtual TMetaVariable GetMetaVariable() const;
};


USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalBooleanMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeBooleanMetaData
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
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalBooleanMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeBooleanMetaData	RangeVariableMetaData;

	public :
		virtual TMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalFloatMetaData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float	Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeFloatMetaData
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalFloatMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeFloatMetaData		RangeVariableMetaData;

public:
	virtual TMetaVariable GetMetaVariable() const override;
	
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalIntegerMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeIntegerMetaData
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
	FKRGBaseVarialeMetaData();

	protected :
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalIntegerMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeIntegerMetaData	RangeVariableMetaData;

	public :
		virtual TMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalLinearColorMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeLinearColorMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FLinearColor Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FLinearColorVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

	public :
		FLinearColorVariableMetaData();

	protected :
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalLinearColorMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeLinearColorMetaData	RangeVariableMetaData;

	public :
		virtual TMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalVector4MetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeVector4MetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector4 Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FVector4VariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

	public :
		FVector4VariableMetaData();

	protected :
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalVector4MetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeVector4MetaData	RangeVariableMetaData;

	public :
		virtual TMetaVariable GetMetaVariable() const override;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FNormalVectorMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Value;
};

USTRUCT(BlueprintType, Blueprintable)
struct METATOOLS_API FRangeVectorMetaData
{
	GENERATED_BODY()

	public :
		UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector	Min;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector Max;
};


USTRUCT(BlueprintType)
struct METATOOLS_API FVectorVariableMetaData : public FBaseVariableMetaData
{
	GENERATED_BODY()

	public :
		FVectorVariableMetaData();

	protected :
		UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Normal", EditConditionHides))
	FNormalVectorMetaData	NormalVariableMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "MetaVariableScope == EMetaVariableScope::Range", EditConditionHides))
	FRangeVectorMetaData	RangeVariableMetaData;

	public :
		virtual TMetaVariable GetMetaVariable() const override;
};
