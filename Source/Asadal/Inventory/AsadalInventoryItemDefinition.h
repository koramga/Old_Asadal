// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreUObject.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AsadalInventoryItemDefinition.generated.h"

/**
 * 
*/

// Represents a fragment of an item definition
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class UAsadalInventoryItemFragment : public UObject
{
	GENERATED_BODY()
	
//public:
//	virtual void OnInstanceCreated(ULyraInventoryItemInstance* Instance) const {}
};

UCLASS(Blueprintable, Const, Abstract)
class ASADAL_API UAsadalInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UAsadalInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Display, Instanced)
	TArray<UAsadalInventoryItemFragment*> Fragments;
	
public:
	const UAsadalInventoryItemFragment* FindFragmentByClass(TSubclassOf<UAsadalInventoryItemFragment> FragmentClass) const;
};
