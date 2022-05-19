// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_GameplayTags.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

UAnimNotify_GameplayTags::UAnimNotify_GameplayTags()
{
}

void UAnimNotify_GameplayTags::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(IsValid(MeshComp)
		&& MeshComp->GetOwner())
	{
		if(MeshComp->GetOwner()->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
		{
			IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(MeshComp->GetOwner());

			UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent();

			if(IsValid(AbilitySystemComponent))
			{
				for(const FAnimNotifyGameplayTagCommand& GameplayTagCommand : GameplayTagCommands)
				{
					for(const FGameplayTag& GameplayTag : GameplayTagCommand.GameplayTagContainer)
					{
						if(EAnimNotifyGameplayTagCommand::Add == GameplayTagCommand.Command)
						{
							AbilitySystemComponent->AddLooseGameplayTag(GameplayTag);
						}
						else if(EAnimNotifyGameplayTagCommand::Remove == GameplayTagCommand.Command)
						{
							AbilitySystemComponent->RemoveLooseGameplayTag(GameplayTag);
						}
					}
				}				
			}
		}
	}
}