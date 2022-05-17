// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Inventory/AsadalInventoryItemDefinition.h"
#include "UObject/Object.h"
#include "InventoryFragment_Item.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UInventoryFragment_Item : public UAsadalInventoryItemFragment
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag											ItemGameplayTag;

protected:
	virtual void OnActivate(TSoftObjectPtr<class ABaseCharacter> BaseCharacter, bool bIsActivate);
	
public :
	virtual bool CanActivate(TSoftObjectPtr<class ABaseCharacter> BaseCharacter, bool bIsActivate) const;
	void SetActivate(TSoftObjectPtr<class ABaseCharacter> BaseCharacter, bool bIsActivate);
	bool HasGameplayTag(const FGameplayTag& GameplayTag);
	const FGameplayTag& GetItemGameplayTag() const;
};
