// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Definition/Fragment/KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASFragment_Eqipment.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASFragment_Eqipment : public UKRGGASFragment
{
	GENERATED_BODY()

public :
	FGameplayTag GetEquipableGameplayTag() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName					DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag			EquipableGameplayTag;
};
