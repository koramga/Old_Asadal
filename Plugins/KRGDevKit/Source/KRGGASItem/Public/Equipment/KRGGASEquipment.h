// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASEquipment.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASEquipment : public UObject
{
	GENERATED_BODY()

public :
	void SetDefinition(class UKRGGASDefinition* Definition);
	void SetAbilitySystemComponent(class UKRGAbilitySystemComponent* InAbilitySystemComponent);

public :
	bool CanPushItem(class UKRGGASItem* Item) const;
	bool PushItem(class UKRGGASItem* Item);
	bool SetActivateItem(class UKRGGASItem* Item);

protected:
	TSoftObjectPtr<class UKRGGASDefinition>				KRGGASDefinition;
	TSoftObjectPtr<class UKRGGASItem>					ActivateItem;
	TArray<TSoftObjectPtr<class UKRGGASItem>>			Items;
	TSoftObjectPtr<class UKRGAbilitySystemComponent>	AbilitySystemComponent;
};
