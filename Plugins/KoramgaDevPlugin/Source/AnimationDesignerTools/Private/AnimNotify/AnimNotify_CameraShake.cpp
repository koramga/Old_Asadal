// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_CameraShake.h"

#include "GameFramework/Character.h"

UAnimNotify_CameraShake::UAnimNotify_CameraShake()
{
#if WITH_EDITORONLY_DATA
	NotifyColor = FColor::Green;
#endif	
}

void UAnimNotify_CameraShake::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(IsValid(CameraShakeBaseClass))
	{
		ACharacter* BaseCharacter = Cast<ACharacter>(MeshComp->GetOwner());

		if(IsValid(BaseCharacter))
		{
			APlayerController* BasePlayerController = Cast<APlayerController>(BaseCharacter->GetController());

			if(IsValid(BasePlayerController))
			{
				if(CameraShakeType == EAnimNotify_CameraShakeType::Local)
				{
					BasePlayerController->ClientStartCameraShake(CameraShakeBaseClass, Scale, PlaySpace, UserPlaySpaceRot);
				}
			
				if(CameraShakeType == EAnimNotify_CameraShakeType::World)
				{
					BasePlayerController->PlayerCameraManager->PlayWorldCameraShake(MeshComp->GetWorld(), CameraShakeBaseClass, Epicenter, InnerRadius, OuterRadius, Falloff, bOrientShakeTowordsEpicenter);
				}
			}
		}		
	}
}

FString UAnimNotify_CameraShake::GetNotifyName_Implementation() const
{
	return Super::GetNotifyName_Implementation();
}
