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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName													DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag											ItemGameplayTag;

protected:
	virtual void OnActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	
public :
	virtual bool CanActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) const;
	void SetActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	bool HasGameplayTag(const FGameplayTag& GameplayTag);
	const FGameplayTag& GetItemGameplayTag() const;
};
