// Fill out your copyright notice in the Description page of Project Settings.


#include "GASComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "Ability/BaseGameplayAbility.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"

bool UGASComponent::GEToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayTag& EventTag)
{
	if(nullptr == TargetAbilitySystemComponent)
	{
		return false;
	}

	if(TargetAbilitySystemComponent->HasMatchingGameplayTag(UAsadalGameplayTags::AvoidStateGameplayTag))
	{
		//회피중이였다.
		return false;
	}
	
	if(bIsLatentEventToTarget)
	{
		GEToTargetLatentEventItems.Add(FGEToTargetEventItem(TargetAbilitySystemComponent, EventTag));
	}
	else
	{
		FGameplayEventData GameplayEventData;
		GameplayEventData.Target = TargetAbilitySystemComponent->GetOwner();

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), EventTag, GameplayEventData);
	}

	return true;
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
					GEToTarget(Item.AbilitySystemComponent.Get(), Item.EventTag);
				}			
			}
			
			OnGEToTargetLatentEvent.Broadcast(GEToTargetLatentEventItems, IsCriticalAbilityFromActionGroup());
			
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

bool UGASComponent::IsCriticalAbilityFromActionGroup()
{
	if(nullptr != ActivateAbilityActionGroup
		&& ActivateAbilityActionGroup->AttackElementIndex >= 0)
	{
		FGameplayAbilitySpec* GameplayAbilitySpec = FindAbilitySpecFromHandle(ActivateAbilityActionGroup->AttackAbilitiesSpecHandles[ActivateAbilityActionGroup->AttackElementIndex]);
		
		bool bIsCritical = false;
		
		for(UGameplayAbility* GameplayAbilityInstance : GameplayAbilitySpec->NonReplicatedInstances)
		{
			const UBaseGameplayAbility* BaseGameplayAbilityInstance = Cast<UBaseGameplayAbility>(GameplayAbilityInstance);

			if(IsValid(BaseGameplayAbilityInstance))
			{				
				const TArray<UGEExecResult*>& ExecResults = BaseGameplayAbilityInstance->GetAbilityGEExecInfos();

				for(const UGEExecResult* ExecResult : ExecResults)
				{
					if(ExecResult->IsCritical())
					{
						return true;
					}
				}
			}
		}
	}	

	return false;
}

bool UGASComponent::TryAvoidAbilityFromActionGroup()
{
	const FGameplayAbilityActionGroup* TryAbilityGroup = ActivateAbilityActionGroup;
	
	if(nullptr == TryAbilityGroup
		|| false == TryAbilityGroup->AvoidAbilitySpecHandle.IsValid())
	{
		//Base로 변경해주고
		TryAbilityGroup = AbilityActionGroupMap.Find(UAsadalGameplayTags::BaseAbilityGameplayTag);
	}

	//Base에도 없다면 실패를 시킨다.
	if(nullptr == TryAbilityGroup
		|| false == TryAbilityGroup->AvoidAbilitySpecHandle.IsValid())
	{
		return false;
	}

	return TryActivateAbility(TryAbilityGroup->AvoidAbilitySpecHandle);
}

bool UGASComponent::TryHitAbilityFromActionGroup()
{
	const FGameplayAbilityActionGroup* TryAbilityGroup = ActivateAbilityActionGroup;
	
	if(nullptr == TryAbilityGroup
		|| false == TryAbilityGroup->HitAbilitySpecHandle.IsValid())
	{
		//Base로 변경해주고
		TryAbilityGroup = AbilityActionGroupMap.Find(UAsadalGameplayTags::BaseAbilityGameplayTag);
	}

	//Base에도 없다면 실패를 시킨다.
	if(nullptr == TryAbilityGroup
		|| false == TryAbilityGroup->HitAbilitySpecHandle.IsValid())
	{
		return false;
	}

	return TryActivateAbility(TryAbilityGroup->HitAbilitySpecHandle);
}

bool UGASComponent::TryAttackAbilityFromActionGroup(int32 ElementIndex)
{
	FGameplayAbilityActionGroup* TryAbilityGroup = ActivateAbilityActionGroup;
	
	if(nullptr == TryAbilityGroup
		|| TryAbilityGroup->AttackAbilitiesSpecHandles.Num() <= ElementIndex
		|| false == TryAbilityGroup->AttackAbilitiesSpecHandles[ElementIndex].IsValid())
	{
		//Base로 변경해주고
		TryAbilityGroup = AbilityActionGroupMap.Find(UAsadalGameplayTags::BaseAbilityGameplayTag);
	}

	//Base에도 없다면 실패를 시킨다.
	if(nullptr == TryAbilityGroup
		|| TryAbilityGroup->AttackAbilitiesSpecHandles.Num() <= ElementIndex
		|| false == TryAbilityGroup->AttackAbilitiesSpecHandles[ElementIndex].IsValid())
	{
		return false;
	}
	
	if(TryActivateAbility(TryAbilityGroup->AttackAbilitiesSpecHandles[ElementIndex]))
	{
		TryAbilityGroup->AttackElementIndex = ElementIndex;
		return true;
	}

	return false;
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
