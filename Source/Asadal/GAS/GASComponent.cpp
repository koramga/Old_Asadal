// Fill out your copyright notice in the Description page of Project Settings.


#include "GASComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"

void UGASComponent::GEToTarget(AActor* Actor, const FGameplayTag& EventTag)
{
	if(bIsLatentEventToTarget)
	{
		GEToTargetLatentEventItems.Add(FGEToTargetEventItem(Actor, EventTag));
	}
	else
	{
		FGameplayEventData GameplayEventData;
		GameplayEventData.Target = Actor;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), EventTag, GameplayEventData);
	}	
}

void UGASComponent::SetGEToTargetLatent(bool InIsLatentEventToTarget)
{
	if(bIsLatentEventToTarget != InIsLatentEventToTarget)
	{
		bIsLatentEventToTarget = InIsLatentEventToTarget;
		
		//True였는데 False이니 모두 뿌린다.
		if(false == InIsLatentEventToTarget)
		{			
			for(const FGEToTargetEventItem& Item : GEToTargetLatentEventItems)
			{
				if(Item.Actor.IsValid())
				{
					GEToTarget(Item.Actor.Get(), Item.EventTag);
				}			
			}
			
			OnGEToTargetLatentEvent.Broadcast(GEToTargetLatentEventItems);
			
			GEToTargetLatentEventItems.Empty();
		}
		//False였는데 True이므로 혹시 모를 LatentEventItems를 날린다.
		else
		{
			GEToTargetLatentEventItems.Empty();
		}
	}
}

void UGASComponent::GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs)
{
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		GameplayAbilitySpecs.Add(&Spec);
	}
}

void UGASComponent::SetActivateAbilityActionGroup(const FGameplayTag& GameplayTag)
{
	ActivateAbilityActionGroup = AbilityActionGroupMap.Find(GameplayTag);
}

const FGameplayAbilityActionGroup* UGASComponent::GetActivateAbilityActionGroup() const
{
	return ActivateAbilityActionGroup;
}

void UGASComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);

	FGameplayTag ActionTag;
	FGameplayTag AbilityTag;
	
	for(const FGameplayTag& GameplayTag : AbilitySpec.Ability->AbilityTags)
	{
		if(GameplayTag.MatchesTag(UAsadalGameplayTags::ActionGameplayTag))
		{
			ActionTag = GameplayTag;
		}
		else if(GameplayTag.MatchesTag(UAsadalGameplayTags::AbilityGameplayTag))
		{
			AbilityTag = GameplayTag;
		}		
	}

	if(ActionTag != FGameplayTag::EmptyTag
		&& AbilityTag != FGameplayTag::EmptyTag)
	{
		FGameplayAbilityActionGroup* ActionGroup = AbilityActionGroupMap.Find(AbilityTag);

		if(nullptr == ActionGroup)
		{
			ActionGroup = &AbilityActionGroupMap.Add(AbilityTag);
		}

		if(nullptr != ActionGroup)
		{
			if(UAsadalGameplayTags::AttackActionGameplayTag == ActionTag)
			{
				ActionGroup->AttackAbilitiesSpecHandles.Add(AbilitySpec.Handle);
			}
			else if(UAsadalGameplayTags::HitActionGameplayTag == ActionTag)
			{
				ActionGroup->HitAbilitySpecHandle = AbilitySpec.Handle;
			}
			else if(UAsadalGameplayTags::AvoidGameplayTag == ActionTag)
			{
				ActionGroup->AvoidAbilitySpecHandle = AbilitySpec.Handle;
			}
		}
	}
}

void UGASComponent::OnTagUpdated(const FGameplayTag& Tag, bool TagExists)
{
	Super::OnTagUpdated(Tag, TagExists);

	OnTagUpdatedEvent.Broadcast(Tag, TagExists);
}
