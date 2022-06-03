// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Fragment/KRGGASFragment_EquipableItem.h"
#include "GameFramework/Character.h"
#include "GAS/KRGAbilitySystemComponent.h"

const TArray<FKRGEquipmentItemFragmentDefinition>& UKRGGASFragment_EquipableItem::GetEquipmentItemDefinitions() const
{
	return EquipmentItemDefinitions;
}

void UKRGGASFragment_EquipableItem::OnActivate(UKRGAbilitySystemComponent* AbilitySystemComponent, bool bIsActivate)
{
	Super::OnActivate(AbilitySystemComponent, bIsActivate);
	/*
	if(true == bIsActivate)
	{
		FActorSpawnParameters ActorSpawnParam;

		ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActorSpawnParam.Owner = AbilitySystemComponent->GetOwner();

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

				SpawnEquipmentActors.Add(NewEquipmentActor);
			}
		}

		//BaseCharacter->LinkSubAnimInstance(ItemGameplayTag);
	}
	else
	{
		for(TSoftObjectPtr<AActor> SpawnActor : SpawnEquipmentActors)
		{
			SpawnActor->Destroy();
		}
		
		SpawnEquipmentActors.Empty();

		//BaseCharacter->UnLinkSubAnimInstance(ItemGameplayTag);
	}
	*/
}

//void UKRGGASFragment_EquipableItem::SetActivateCollisions(bool bIsActivate)
//{
//	for(TSoftObjectPtr<ABaseEquipment> SpawnActor : SpawnEquipmentActors)
//	{
//		SpawnActor->SetActivateCollision(bIsActivate);
//	}
//}

const TArray<TSoftObjectPtr<AActor>>& UKRGGASFragment_EquipableItem::GetSpawnEquipmentActors() const
{
	return Temp;
}