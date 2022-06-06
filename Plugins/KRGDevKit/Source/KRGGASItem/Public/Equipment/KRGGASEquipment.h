// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGGASDefinitionObject.h"
#include "KRGGASEquipment.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASEquipment : public UKRGGASDefinitionObject
{
	GENERATED_BODY()

public :
	bool AddExtraItem(class UKRGGASItem* Item);
	bool SetActivateNextExtraItem();
	bool SetActivateItem(class UKRGGASItem* Item);
	FGameplayTag GetEquipmentGameplayTag() const;
	UKRGGASItem* GetActivateItem() const;
	
protected :
	virtual bool CanActivateItem(class UKRGGASItem* Item) const;
	virtual void UpdateActivateItem(class UKRGGASItem* Item);
	
protected:
	virtual bool CanUpdateDefinition(UKRGGASDefinition* Definition) const override;

protected:
	TSoftObjectPtr<class UKRGGASItem>					ActivateItem;
	TArray<TSoftObjectPtr<class UKRGGASItem>>			ExtraItems;
};
