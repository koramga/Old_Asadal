// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify_SetActivateEquipment.h"

#include "Asadal/Actor/Equipment/BaseEquipment.h"
#include "Asadal/Character/BaseCharacter.h"

FString UAnimNotify_SetActivateEquipment::GetNotifyName_Implementation() const
{
	return TEXT("EquipmentActivate");
}

void UAnimNotify_SetActivateEquipment::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* Owner = MeshComp->GetOwner();

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Owner);

	if(IsValid(BaseCharacter))
	{
		BaseCharacter->SetActivateEquipment(ActivateGameplayTag, bIsActivate);
	}
}
