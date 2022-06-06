// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"
#include "Definition/KRGGASDefinition.h"
#include "Definition/KRGGASDefinitionObject.h"
#include "UObject/Object.h"
#include "KRGGASItem.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASItem : public UKRGGASDefinitionObject
{
	GENERATED_BODY()
	
public :
	FGameplayTag GetItemGameplayTag() const;
	FGameplayTagContainer GetEquipmentGameplayTag() const;
	
protected:
	virtual bool CanUpdateDefinition(UKRGGASDefinition* Definition) const override;
	virtual void UpdateDefinition(UKRGGASDefinition* Definition) override;
	virtual void OnActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	virtual void Clear();
	
public :
	virtual bool CanActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) const;
	bool IsActivate() const;
	bool SetActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	
protected:
	FActiveGameplayEffectHandle						ActivateGameplayEffectHandle;
	TArray<TSoftObjectPtr<class AActor>>			SpawnActors;
	bool											IsActivateItem = false;
};
