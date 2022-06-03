// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASFragment_Item.h"
#include "UObject/Object.h"
#include "KRGGASFragment_EquipableItem.generated.h"

/**
 * 
*/

USTRUCT(BlueprintType)
struct FKRGEquipmentItemFragmentDefinition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class AActor>				SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName									AttachBoneName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform								Transform;
};

UCLASS()
class KRGGASITEM_API UKRGGASFragment_EquipableItem : public UKRGGASFragment_Item
{
	GENERATED_BODY()

public :
	const TArray<FKRGEquipmentItemFragmentDefinition>& GetEquipmentItemDefinitions() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FKRGEquipmentItemFragmentDefinition>				EquipmentItemDefinitions;

	TArray<TSoftObjectPtr<AActor>> Temp;
	
protected:
	virtual void OnActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) override;

public :
	//void SetActivateCollisions(bool bIsActivate);
	const TArray<TSoftObjectPtr<class AActor>>& GetSpawnEquipmentActors() const;
};
