// Fill out your copyright notice in the Description page of Project Settings.


#include "GASComponent.h"

#include "AbilitySystemBlueprintLibrary.h"

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

			GEToTargetLatentEventItems.Empty();
		}
		//False였는데 True이므로 혹시 모를 LatentEventItems를 날린다.
		else
		{
			GEToTargetLatentEventItems.Empty();
		}
	}
}
