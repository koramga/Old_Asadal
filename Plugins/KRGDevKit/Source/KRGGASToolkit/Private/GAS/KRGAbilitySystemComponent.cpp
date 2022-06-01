// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Definition/Fragment/KRGGASFragment_Abilities.h"
#include "Definition/Fragment/KRGGASFragment_AttributeSets.h"
#include "Definition/Fragment/KRGGASFragment_PersonalInfo.h"


// Sets default values for this component's properties
UKRGAbilitySystemComponent::UKRGAbilitySystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UKRGAbilitySystemComponent::CanGEExec(UAbilitySystemComponent* AbilitySystemComponent,
	UAbilitySystemComponent* TargetAbilitySystemComponent)
{
	return true;
}

void UKRGAbilitySystemComponent::UpdateAbilitiesFromFragment(UKRGGASFragment_Abilities* AbilitiesFragment)
{
	if(IsValid(AbilitiesFragment))
	{
		
	}
}

bool UKRGAbilitySystemComponent::GEExecToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent,
                                                const FGameplayTag& EventTag)
{
	if(nullptr == TargetAbilitySystemComponent)
	{
		return false;
	}

	if(false == CanGEExec(this, TargetAbilitySystemComponent))
	{
		return false;
	}

	//if(TargetAbilitySystemComponent->HasMatchingGameplayTag(UAsadalGameplayTags::AvoidStateGameplayTag))
	//{
	//	//회피중이였다.
	//	return false;
	//}
	
	if(bIsLatentGEExec)
	{
		GEExecEvents.Add(FGEEExecEvent(TargetAbilitySystemComponent, EventTag));
	}
	else
	{
		FGameplayEventData GameplayEventData;
		GameplayEventData.Target = TargetAbilitySystemComponent->GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), EventTag, GameplayEventData);
	}

	return true;	
}

void UKRGAbilitySystemComponent::SetGEExecLatent(bool InIsLatentGEExec)
{
	if(bIsLatentGEExec != InIsLatentGEExec)
	{
		bIsLatentGEExec = InIsLatentGEExec;
		
		//True였는데 False이니 모두 뿌린다.
		if(false == InIsLatentGEExec)
		{			
			for(const FGEEExecEvent& ExecEvent : GEExecEvents)
			{
				if(ExecEvent.Actor.IsValid())
				{
					GEExecToTarget(ExecEvent.AbilitySystemComponent.Get(), ExecEvent.EventTag);
				}			
			}
			
			OnGEExecLatentEvent.Broadcast(GEExecEvents, IsCriticalAbility());
			
			GEExecEvents.Empty();
		}
		//False였는데 True이므로 혹시 모를 LatentEventItems를 날린다.
		else
		{
			GEExecEvents.Empty();
		}
	}
}

bool UKRGAbilitySystemComponent::IsCriticalAbility()
{
	return false;
}

void UKRGAbilitySystemComponent::SetKRGGASDefinition(UKRGGASDefinition* InKRGGASDefinition)
{
	KRGGASDefinition = InKRGGASDefinition;
}

void UKRGAbilitySystemComponent::UpdateFromKRGGASDefinition()
{
	if(KRGGASDefinition.IsValid())
	{
		UpdateAbilitiesFromFragment(KRGGASDefinition->FindFragment<UKRGGASFragment_Abilities>());
		UKRGGASFragment_AttributeSets* AttributeSetsFragment = KRGGASDefinition->FindFragment<UKRGGASFragment_AttributeSets>();
		UKRGGASFragment_PersonalInfo* PersonalInfo = KRGGASDefinition->FindFragment<UKRGGASFragment_PersonalInfo>();
	}
}

void UKRGAbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
}

void UKRGAbilitySystemComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);

	OnTagUpdatedEvent.Broadcast(Tag, TagExists);
}
