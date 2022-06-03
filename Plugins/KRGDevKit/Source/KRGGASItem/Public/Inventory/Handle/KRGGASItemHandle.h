// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGGASDefinition.h"
#include "UObject/Object.h"
#include "KRGGASItemHandle.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASITEM_API UKRGGASItemHandle : public UObject
{
	GENERATED_BODY()

public :
	void SetDefinition(UKRGGASDefinition* Definition);
	const TSoftObjectPtr<class UKRGGASItem>& GetItem() const;

protected:
	TSoftObjectPtr<class UKRGGASItem>	KRGGASItem;
};
