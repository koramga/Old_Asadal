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
	bool CanPushItem(class UKRGGASItem* Item) const;
	bool PushItem(class UKRGGASItem* Item);
	bool SetActivateItem(class UKRGGASItem* Item);

protected:
	virtual bool CanUpdateDefinition(UKRGGASDefinition* Definition) const override;

protected:
	TSoftObjectPtr<class UKRGGASItem>					ActivateItem;
	TArray<TSoftObjectPtr<class UKRGGASItem>>			Items;
};
