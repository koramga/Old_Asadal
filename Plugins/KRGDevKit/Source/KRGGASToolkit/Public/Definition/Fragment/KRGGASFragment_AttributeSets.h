// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASFragment.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "KRGGASFragment_AttributeSets.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct FKRGGASAttributeSetInfo
{
	GENERATED_BODY()


public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer	ActivateGameplayTagContainer;

	UPROPERTY(EditAnywhere)
	FAttributeDefaults		AttributeDefaults;
};

UCLASS()
class KRGGASTOOLKIT_API UKRGGASFragment_AttributeSets : public UKRGGASFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKRGGASAttributeSetInfo>	AttributeSetInfos; 
};
