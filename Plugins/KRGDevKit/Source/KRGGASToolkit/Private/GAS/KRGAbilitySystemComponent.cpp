// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGGASToolkit/Public/GAS/KRGAbilitySystemComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Ability/KRGGameplayAbility.h"


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
		const TArray<FKRGGASAbilityInfo>& AbilityInfos = AbilitiesFragment->GetGASAbilityInfos();

		for(const FKRGGASAbilityInfo& AbilityInfo : AbilityInfos)
		{
			for(const FGameplayTag& GameplayTag : AbilityInfo.ActivateGameplayTagContainer)
			{
				if(false == FragmentAbilityMap.Contains(GameplayTag))
				{
					FragmentAbilityMap.Add(GameplayTag);							
				}

				TArray<FKRGGASAbilityInfo>& KRGGASAbilityInfos = FragmentAbilityMap.FindChecked(GameplayTag);

				KRGGASAbilityInfos.Add(AbilityInfo);
			}
			/*
			FGameplayAbilitySpecHandle AbilitySpecHandle;
			
			if(GetOwner()->HasAuthority() && IsValid(AbilityInfo.AbilityClass))
			{
				AbilitySpecHandle = GiveAbility(FGameplayAbilitySpec(FGameplayAbilitySpec(AbilityInfo.AbilityClass, 0, 0)));

				if(AbilitySpecHandle.IsValid())
				{
					InitAbilityActorInfo(GetOwner(), GetOwner());

					//여기서부터 조정이 필요합니다.
					for(const FGameplayTag& GameplayTag : AbilityInfo.ActivateGameplayTagContainer)
					{
						if(false == FragmentAbilitiesMap.Contains(GameplayTag))
						{
							FragmentAbilitiesMap.Add(GameplayTag);							
						}

						TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles = FragmentAbilitiesMap.FindChecked(GameplayTag);

						AbilitySpecHandles.Add(AbilitySpecHandle);
					}
				}
			}
			*/
		}
	}
}

void UKRGAbilitySystemComponent::UpdateAttributeSets(UKRGGASFragment_AttributeSets* AttributeSetFragment)
{
	if(IsValid(AttributeSetFragment))
	{
		const TArray<FKRGGASAttributeSetInfo>& KRGGASAttributeSetInfos = AttributeSetFragment->GetAttributeSetInfos();

		for(const FKRGGASAttributeSetInfo& KRGGASAttributeSetInfo : KRGGASAttributeSetInfos)
		{
			for(const FGameplayTag& GameplayTag : KRGGASAttributeSetInfo.ActivateGameplayTagContainer)
			{
				if(false == FragmentAttributeSetMap.Contains(GameplayTag))
				{
					FragmentAttributeSetMap.Add(GameplayTag);
				}
		
				TArray<FKRGGASAttributeSetInfo>& GASAttributeSetInfos = FragmentAttributeSetMap.FindChecked(GameplayTag);
		
				GASAttributeSetInfos.Add(KRGGASAttributeSetInfo);
			}
		}
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

bool UKRGAbilitySystemComponent::UpdateFromKRGGASDefinition()
{
	if(KRGGASDefinition.IsValid())
	{
		UpdateAbilitiesFromFragment(KRGGASDefinition->FindFragment<UKRGGASFragment_Abilities>());
		UpdateAttributeSets(KRGGASDefinition->FindFragment<UKRGGASFragment_AttributeSets>());
		//UKRGGASFragment_AttributeSets* AttributeSetsFragment = KRGGASDefinition->FindFragment<UKRGGASFragment_AttributeSets>();
		UKRGGASFragment_PersonalInfo* PersonalInfo = KRGGASDefinition->FindFragment<UKRGGASFragment_PersonalInfo>();

		return true;
	}

	return false;
}

bool UKRGAbilitySystemComponent::ActivateFragmentAbility(const FGameplayTag& GameplayTag)
{
	if(false == FragmentAbilityMap.Contains(GameplayTag))
	{
		return false;
	}
	
	ClearAbilityFromActivateFragment();
	
	TArray<FKRGGASAbilityInfo>& KRGGASAbilityInfos = FragmentAbilityMap.FindChecked(GameplayTag);

	for(FKRGGASAbilityInfo& KRGGASAbilityInfo : KRGGASAbilityInfos)
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle;
			
		if(GetOwner()->HasAuthority() && IsValid(KRGGASAbilityInfo.AbilityClass))
		{
			AbilitySpecHandle = GiveAbility(FGameplayAbilitySpec(FGameplayAbilitySpec(KRGGASAbilityInfo.AbilityClass, 0, 0)));

			if(AbilitySpecHandle.IsValid())
			{
				InitAbilityActorInfo(GetOwner(), GetOwner());

				ActivateAbilityFragmentHandles.Add(FKRGGASFragmentAbilityHandle(AbilitySpecHandle, &KRGGASAbilityInfo));
			}
			else
			{
				ClearAbilityFromActivateFragment();
				return false;
			}
		}
	}

	return true;
}

bool UKRGAbilitySystemComponent::ActivateFragmentAttributeSet(const FGameplayTag& GameplayTag)
{
	if(false == FragmentAttributeSetMap.Contains(GameplayTag))
	{
		return false;
	}
	
	ClearAttributeFromActivateFragement();

	TArray<FKRGGASAttributeSetInfo>& KRGGASAttributeSetInfos = FragmentAttributeSetMap.FindChecked(GameplayTag);

	for(FKRGGASAttributeSetInfo& KRGGASAttributeSetInfo : KRGGASAttributeSetInfos)
	{
		const UAttributeSet* AttributeSet = InitStats(KRGGASAttributeSetInfo.AttributeDefaults.Attributes, KRGGASAttributeSetInfo.AttributeDefaults.DefaultStartingTable);

		if(IsValid(AttributeSet))
		{
			ActivateAttributeSetFragmentHandles.Add(FKRGGASFragmentAttributeSetHandle(AttributeSet, &KRGGASAttributeSetInfo));
		}
		else
		{
			ClearAttributeFromActivateFragement();
			return false;
		}
	}

	return true;
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

void UKRGAbilitySystemComponent::ClearAbilityFromActivateFragment()
{
	for(const FKRGGASFragmentAbilityHandle& ActivateAbilityFragmentHandle : ActivateAbilityFragmentHandles)
	{
		ClearAbility(ActivateAbilityFragmentHandle.GameplayAbilitySpecHandle);
	}

	ActivateAbilityFragmentHandles.Empty();
}

void UKRGAbilitySystemComponent::ClearAttributeFromActivateFragement()
{
	//Server, Client 연동 시 매우 위험할 수 있음.
	//아직 Server와 연동할 생각은 없지만 추후에 Server와 연동 시 분명히 고려해야할 사항이 됨.
	
	for(const FKRGGASFragmentAttributeSetHandle& ActivateAttirbuteSetFragementHandle : ActivateAttributeSetFragmentHandles)
	{		
		GetSpawnedAttributes_Mutable().Remove(const_cast<UAttributeSet*>(ActivateAttirbuteSetFragementHandle.AttributeSet));
	}
}