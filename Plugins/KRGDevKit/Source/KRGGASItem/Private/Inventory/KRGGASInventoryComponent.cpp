// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/KRGGASInventoryComponent.h"
#include "GAS/KRGAbilitySystemComponent.h"
#include "Item/KRGGASItem.h"
#include "Item/Fragment/KRGGASFragment_Item.h"

// Sets default values for this component's properties
UKRGGASInventoryComponent::UKRGGASInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UKRGGASInventoryComponent::SetKRGAbilitySystemComponent(UKRGAbilitySystemComponent* AbilitySystemComponent)
{
	KRGAbilitySystemComponent = AbilitySystemComponent;
}

const UKRGGASItem* UKRGGASInventoryComponent::AddItem(UKRGGASDefinition* Definition)
{
	if(IsValid(Definition))
	{
		if(IsValid(Definition->FindFragment<UKRGGASFragment_Item>()))
		{
			FKRGInventoryItem KRGInventoryItem;

			KRGInventoryItem.Item = NewObject<UKRGGASItem>();
			
			KRGInventoryItem.Item->SetDefinition(Definition);
	
			KRGInventoryItems.Add(KRGInventoryItem);

			return KRGInventoryItem.Item.Get();
		}
	}

	return nullptr;
}

bool UKRGGASInventoryComponent::ActivateItem(const UKRGGASItem* Item, bool bIsActivate)
{
	int32 Index = FindIndexFromHandle(Item);

	if(Index >= 0)
	{
		return KRGInventoryItems[Index].Item->SetActivate(KRGAbilitySystemComponent.Get(), bIsActivate);
	}

	return false;
}

bool UKRGGASInventoryComponent::RemoveItem(const UKRGGASItem* Item)
{
	if(true == Item->IsActivate())
	{
		return false;
	}

	int32 Index = FindIndexFromHandle(Item);

	if(Index >= 0
		&& KRGInventoryItems.Num() > Index)
	{
		KRGInventoryItems.RemoveAt(Index);

		return true;
	}

	return false;	
}

int32 UKRGGASInventoryComponent::FindIndexFromHandle(const UKRGGASItem* Item)
{
	int32 Index = 0;
	
	for(FKRGInventoryItem& InventoryItem : KRGInventoryItems)
	{
		if(InventoryItem.Item == Item)
		{
			return Index;
		}
		
		++Index;
	}

	return -1;
}

// Called when the game starts
void UKRGGASInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UKRGGASInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

