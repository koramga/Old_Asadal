// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Definition/Fragment/KRGGASFragment.h"
#include "KRGGASFragment_Item.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASFragment_Item : public UKRGGASFragment
{
	GENERATED_BODY()

public :
	const FGameplayTag& GetItemGameplayTag() const;
	bool CanCounting() const;
	int32 GetMaxCount() const;
	FName GetDisplayName() const;	

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName													DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag											ItemGameplayTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool													bCanCounting = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (EditCondition = "CanCounting", EditConditionHides) )
	int32													MaxCount = 32;

public :
	virtual bool CanActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) const;
};
