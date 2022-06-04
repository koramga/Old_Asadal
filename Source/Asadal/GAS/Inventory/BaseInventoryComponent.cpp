// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseInventoryComponent.h"

#include "Definition/KRGGASDefinition.h"
#include "Item/Fragment/KRGGASFragment_Item.h"


// Sets default values for this component's properties
UBaseInventoryComponent::UBaseInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBaseInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for(UDataAsset* DataAsset : ItemDefinitions)
	{
		UKRGGASDefinition* KRGGASDefinition = Cast<UKRGGASDefinition>(DataAsset);

		if(IsValid(KRGGASDefinition))
		{
			UKRGGASFragment_Item* KRGItemFragment = KRGGASDefinition->FindFragment<UKRGGASFragment_Item>();

			if(IsValid(KRGItemFragment))
			{
				AddItem(KRGGASDefinition);
			}
		}
	}
}


// Called every frame
void UBaseInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

