// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_EquippableItem.h"

#include "Asadal/Actor/Object/Equipment/BaseEquipment.h"
#include "Asadal/Character/BaseCharacter.h"

void UInventoryFragment_EquippableItem::SetEquip(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsEquip)
{
	if(true == bIsEquip)
	{
		FActorSpawnParameters ActorSpawnParam;

		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActorSpawnParam.Owner = BaseCharacter.Get();

		for(const FEquipmentItemDefinition& EquipmentItemDefinition : EquipmentItemDefinitions)
		{		
			ABaseEquipment* NewBaseEquipmentActor = GetWorld()->SpawnActor<ABaseEquipment>(EquipmentItemDefinition.BaseEquipmentActorClass, EquipmentItemDefinition.Transform, ActorSpawnParam);

			if(IsValid(NewBaseEquipmentActor))
			{
				if(false == EquipmentItemDefinition.AttachBoneName.IsNone())
				{
					NewBaseEquipmentActor->AttachToComponent(BaseCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, EquipmentItemDefinition.AttachBoneName);
				}

				SpawnEquipmentActors.Add(NewBaseEquipmentActor);
			}
		}

		BaseCharacter->AddLooseGameplayTag(EquipmentGameplayTag);
	}
	else
	{
		for(TSoftObjectPtr<ABaseEquipment> SpawnActor : SpawnEquipmentActors)
		{
			SpawnActor->Destroy();
		}
		
		SpawnEquipmentActors.Empty();

		BaseCharacter->RemoveLooseGameplayTag(EquipmentGameplayTag); 
	}
}

bool UInventoryFragment_EquippableItem::HasGameplayTag(FGameplayTag GameplayTag)
{
	return EquipmentGameplayTag.MatchesTag(GameplayTag);
}

void UInventoryFragment_EquippableItem::SetActivateCollisions(bool bIsActivate)
{
	for(TSoftObjectPtr<ABaseEquipment> SpawnActor : SpawnEquipmentActors)
	{
		SpawnActor->SetActivateCollision(bIsActivate);
	}
}

FGameplayTag UInventoryFragment_EquippableItem::GetEquipmentGameplayTag() const
{
	return EquipmentGameplayTag;
}

const TArray<TSoftObjectPtr<ABaseEquipment>>& UInventoryFragment_EquippableItem::GetSpawnEquipmentActors() const
{
	return SpawnEquipmentActors;
}
