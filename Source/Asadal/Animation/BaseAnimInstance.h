// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "BaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	Angle;

public :
	void SetSpeed(float InSpeed);
	void SetAngle(float InAngle);
};
