// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGGASDefinition.h"
#include "Handle/KRGGASItemHandle.h"
#include "UObject/Object.h"
#include "KRGBaseInventory.generated.h"

/**
 * 
 */

USTRUCT()
struct FKRGInventoryItem
{
	GENERATED_BODY()

	TSoftObjectPtr<UKRGGASItemHandle>	KRGGASItemHandle;

	bool operator == (const FKRGInventoryItem& rhs) const
	{
		return KRGGASItemHandle == rhs.KRGGASItemHandle;
	}

	bool operator != (const FKRGInventoryItem& rhs) const
	{
		return KRGGASItemHandle != rhs.KRGGASItemHandle;
	}
};

UCLASS()
class KRGGASITEM_API UKRGBaseInventory : public UObject
{
	GENERATED_BODY()

public :
	void SetAbilitySystemComponent(class UKRGAbilitySystemComponent* InKRGAbilitySystemComponent);
	
public :
	const UKRGGASItemHandle* AddItem(UKRGGASDefinition* Definition);
	bool ActivateItem(const UKRGGASItemHandle* Handle, bool bIsActivate);
	bool RemoveItem(const UKRGGASItemHandle* Handle);

protected:
	int32 FindIndexFromHandle(const UKRGGASItemHandle* Handle);

protected:
	TArray<FKRGInventoryItem>		KRGInventoryItems;
	TSoftObjectPtr<class UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
};
