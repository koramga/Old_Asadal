// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/KRGGASItem.h"

#include "GameFramework/Character.h"
#include "Item/Fragment/KRGGASFragment_EquipableItem.h"
#include "Item/Fragment/KRGGASFragment_Item.h"
#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"

void UKRGGASItem::SetDefinition(UKRGGASDefinition* Definition)
{
	if(KRGGASDefinition.IsValid())
	{
		Clear();
	}

	KRGGASDefinition = Definition;
}

void UKRGGASItem::OnActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate)
{
	if(bIsActivate)
	{
		//UKRGGASFragment_Item* Item = KRGGASDefinition->FindFragment<UKRGGASFragment_Item>();
		UKRGGASFragment_EquipableItem* EquipableItem = KRGGASDefinition->FindFragment<UKRGGASFragment_EquipableItem>();

		if(IsValid(EquipableItem))
		{
			FActorSpawnParameters ActorSpawnParam;

			ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ActorSpawnParam.Owner = AbilitySystemComponent->GetOwner();

			const TArray<FKRGEquipmentItemFragmentDefinition>& EquipmentItemDefinitions = EquipableItem->GetEquipmentItemDefinitions();

			for(const FKRGEquipmentItemFragmentDefinition& EquipmentItemDefinition : EquipmentItemDefinitions)
			{		
				AActor* NewEquipmentActor = ActorSpawnParam.Owner->GetWorld()->SpawnActor<AActor>(EquipmentItemDefinition.SpawnActorClass, EquipmentItemDefinition.Transform, ActorSpawnParam);

				if(IsValid(NewEquipmentActor))
				{				
					if(false == EquipmentItemDefinition.AttachBoneName.IsNone())
					{					
						ACharacter* Character = Cast<ACharacter>(AbilitySystemComponent->GetOwner());
					
						NewEquipmentActor->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, EquipmentItemDefinition.AttachBoneName);
					}

					SpawnActors.Add(NewEquipmentActor);
				}
			}			
		}

		IsActivateItem = true;
	}
	else
	{
		Clear();

		IsActivateItem = false;
	}
}

void UKRGGASItem::Clear()
{
	if(IsActivateItem)
	{
		for(TSoftObjectPtr<AActor> SpawnActor : SpawnActors)
		{
			SpawnActor->Destroy();
		}
		
		SpawnActors.Empty();		
	}
}

bool UKRGGASItem::CanActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate) const
{
	TArray<UKRGGASFragment_Item*> Items = KRGGASDefinition->FindFragments<UKRGGASFragment_Item>();

	for(UKRGGASFragment_Item* Item : Items)
	{
		if(false == Item->CanActivate(AbilitySystemComponent, bIsActivate))
		{
			return false;
		}
	}

	return true;
}

bool UKRGGASItem::IsActivate() const
{
	return IsActivateItem;
}

bool UKRGGASItem::SetActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate)
{
	if(CanActivate(AbilitySystemComponent, bIsActivate))
	{
		OnActivate(AbilitySystemComponent, bIsActivate);

		return true;
	}

	return false;
}
