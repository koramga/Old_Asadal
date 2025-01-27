﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyState_StrikeTrail.h"

#include "Asadal/Character/BaseCharacter.h"

void UAnimNotifyState_StrikeTrail::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                               float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);	

	AActor* Owner = MeshComp->GetOwner();

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Owner);

	if(IsValid(BaseCharacter))
	{
		UGASComponent* GASComponent = Cast<UGASComponent>(BaseCharacter->GetAbilitySystemComponent());

		if(IsValid(GASComponent))
		{
			GASComponent->SetGEExecLatent(true);
			BaseCharacter->TryActivateEquipment(ActivateGameplayTag, true);	
		}
	}
}

void UAnimNotifyState_StrikeTrail::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UAnimNotifyState_StrikeTrail::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	AActor* Owner = MeshComp->GetOwner();

	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(Owner);

	if(IsValid(BaseCharacter))
	{
		UGASComponent* GASComponent = Cast<UGASComponent>(BaseCharacter->GetAbilitySystemComponent());

		if(IsValid(GASComponent))
		{
			GASComponent->SetGEExecLatent(false);
			BaseCharacter->TryActivateEquipment(ActivateGameplayTag, false);
		}
	}
}
