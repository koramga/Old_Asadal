// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "KRGGASFragment.h"
#include "UObject/Object.h"
#include "KRGGASFragment_Abilities.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FKRGGASAbilityInfo
{
	GENERATED_BODY()

public :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName									Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer					ActivateGameplayTagContainer;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D*								IconTexture;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UKRGGameplayAbility>	AbilityClass;
};

USTRUCT()
struct FKRGGASFragmentAbilityHandle
{
	GENERATED_BODY()

	FKRGGASFragmentAbilityHandle()
		: GameplayAbilitySpecHandle(FGameplayAbilitySpecHandle()), KRGGASAbilityInfo(nullptr)
	{}
	
	FKRGGASFragmentAbilityHandle(FGameplayAbilitySpecHandle Handle, const FKRGGASAbilityInfo* Info)
		: GameplayAbilitySpecHandle(Handle), KRGGASAbilityInfo(Info)
	{
		
	}

public :
	FGameplayAbilitySpecHandle	GameplayAbilitySpecHandle;
	const FKRGGASAbilityInfo*	KRGGASAbilityInfo;
};

UCLASS()
class KRGGASTOOLKIT_API UKRGGASFragment_Abilities : public UKRGGASFragment
{
	GENERATED_BODY()

public :
	const TArray<FKRGGASAbilityInfo>& GetGASAbilityInfos() const;

protected :
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKRGGASAbilityInfo>	KRGGASAbilityInfos;
};
