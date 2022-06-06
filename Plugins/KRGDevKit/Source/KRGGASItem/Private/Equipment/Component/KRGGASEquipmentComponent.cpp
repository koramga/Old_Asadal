// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/Component/KRGGASEquipmentComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Definition/KRGGASDefinition.h"
#include "Equipment/KRGGASEquipment.h"
#include "Equipment/Fragment/KRGGASFragment_Eqipment.h"
#include "GAS/KRGAbilitySystemComponent.h"

// Sets default values for this component's properties
UKRGGASEquipmentComponent::UKRGGASEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UKRGGASEquipmentComponent::SetKRGAbilitySystemComponent(UKRGAbilitySystemComponent* AbilitySystemComponent)
{
	KRGAbilitySystemComponent = AbilitySystemComponent;
}

bool UKRGGASEquipmentComponent::AddDefinition(UKRGGASDefinition* Definition)
{
	if(KRGAbilitySystemComponent.IsValid()
		&& IsValid(Definition))
	{
		UKRGGASFragment_Eqipment* FragmentEquipment = Definition->FindFragment<UKRGGASFragment_Eqipment>();	

		if(IsValid(FragmentEquipment))
		{
			//문제없다고 판단한다.

			UKRGGASEquipment* KRGGASEquipment = NewObject<UKRGGASEquipment>();

			KRGGASEquipment->SetDefinition(Definition);
			KRGGASEquipment->SetKRGAbilitySystemComponent(KRGAbilitySystemComponent.Get());

			KRGGASEquipments.Add(KRGGASEquipment);

			return true;
		}
	}

	return false;
}


// Called when the game starts
void UKRGGASEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	if(false == KRGAbilitySystemComponent.IsValid())
	{
		if(GetOwner()->GetClass()->ImplementsInterface(UAbilitySystemComponent::StaticClass()))
		{
			IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(GetOwner());

			if(nullptr != AbilitySystemInterface)
			{
				KRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());
			}
		}		
	}

	if(KRGAbilitySystemComponent.IsValid())
	{
		for(UDataAsset* KRGGASEquipmentDefinition : KRGGASEquipmentDefinitions)
		{
			UKRGGASDefinition* KRGGASDefinition = Cast<UKRGGASDefinition>(KRGGASEquipmentDefinition);

			if(IsValid(KRGGASDefinition))
			{
				AddDefinition(KRGGASDefinition);
			}
		}
	}
}


// Called every frame
void UKRGGASEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

