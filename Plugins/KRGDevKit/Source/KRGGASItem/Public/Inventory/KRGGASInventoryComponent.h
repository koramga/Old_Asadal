// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item/KRGGASItem.h"
//#include "Handle/KRGGASItemHandle.h"
#include "KRGGASInventoryComponent.generated.h"

USTRUCT()
struct FKRGInventoryItem
{
	GENERATED_BODY()
	TSoftObjectPtr<UKRGGASItem>	Item;
	bool operator == (const FKRGInventoryItem& rhs) const
	{
		return Item == rhs.Item;
	}
	bool operator != (const FKRGInventoryItem& rhs) const
	{
		return Item != rhs.Item;
	}
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRGGASITEM_API UKRGGASInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKRGGASInventoryComponent();

	void SetKRGAbilitySystemComponent(class UKRGAbilitySystemComponent* AbilitySystemComponent);

public :
	TArray<TSoftObjectPtr<UKRGGASItem>> GetItemsFromTag(const FGameplayTag& Tag);
	UKRGGASItem* AddItem(UKRGGASDefinition* Definition);
	bool ActivateItem(const UKRGGASItem* Item, bool bIsActivate);
	bool RemoveItem(const UKRGGASItem* Item);

protected:
	int32 FindIndexFromHandle(const UKRGGASItem* Item);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	TArray<FKRGInventoryItem>							KRGInventoryItems;
	TSoftObjectPtr<class UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
	
};
