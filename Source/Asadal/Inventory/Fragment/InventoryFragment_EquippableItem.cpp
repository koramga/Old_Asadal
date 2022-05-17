// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryFragment_EquippableItem.h"

#include "Asadal/Actor/Object/Equipment/BaseEquipment.h"
#include "Asadal/Character/BaseCharacter.h"

void UInventoryFragment_EquippableItem::OnActivate(TSoftObjectPtr<ABaseCharacter> BaseCharacter, bool bIsActivate)
{
	Super::OnActivate(BaseCharacter, bIsActivate);
	
	if(true == bIsActivate)
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

		BaseCharacter->LinkSubAnimInstance(ItemGameplayTag);
	}
	else
	{
		for(TSoftObjectPtr<ABaseEquipment> SpawnActor : SpawnEquipmentActors)
		{
			SpawnActor->Destroy();
		}
		
		SpawnEquipmentActors.Empty();

		BaseCharacter->UnLinkSubAnimInstance(ItemGameplayTag);
	}
}

void UInventoryFragment_EquippableItem::SetActivateCollisions(bool bIsActivate)
{
	for(TSoftObjectPtr<ABaseEquipment> SpawnActor : SpawnEquipmentActors)
	{
		SpawnActor->SetActivateCollision(bIsActivate);
	}
}

const TArray<TSoftObjectPtr<ABaseEquipment>>& UInventoryFragment_EquippableItem::GetSpawnEquipmentActors() const
{
	return SpawnEquipmentActors;
}