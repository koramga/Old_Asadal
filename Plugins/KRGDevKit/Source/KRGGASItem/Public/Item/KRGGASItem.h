// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGGASDefinition.h"
#include "UObject/Object.h"
#include "KRGGASItem.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASItem : public UObject
{
	GENERATED_BODY()
	
public :
	void SetDefinition(UKRGGASDefinition* Definition);
	
protected:
	virtual void OnActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	virtual void Clear();
	
public :
	virtual bool CanActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) const;
	bool IsActivate() const;
	void SetActivate(class UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate);
	
protected:
	TSoftObjectPtr<UKRGGASDefinition>				KRGGASDefinition;
	TArray<TSoftObjectPtr<class AActor>>			SpawnActors;
	bool											IsActivateItem = false;
};
