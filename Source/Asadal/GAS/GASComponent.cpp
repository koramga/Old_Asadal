// Fill out your copyright notice in the Description page of Project Settings.


#include "GASComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "Ability/BaseGameplayAbility.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"

void UGASComponent::GetAbilitySpecs(TArray<const FGameplayAbilitySpec*>& GameplayAbilitySpecs)
{
	for (FGameplayAbilitySpec& Spec : ActivatableAbilities.Items)
	{
		GameplayAbilitySpecs.Add(&Spec);
	}
}

const FGameplayAbilityActionGroup* UGASComponent::GetActivateAbilityActionGroup() const
{
	return &ActivateAbilityActionGroup;
}

bool UGASComponent::TryAvoidAbilityFromActionGroup()
{
	if(ActivateAbilityActionGroup.AvoidAbilityFragmentHandle.IsValid())
	{
		return TryActivateAbility(ActivateAbilityActionGroup.AvoidAbilityFragmentHandle.GameplayAbilitySpecHandle);
	}

	return false;
}

bool UGASComponent::TryHitAbilityFromActionGroup()
{
	if(ActivateAbilityActionGroup.HitAbilityFragmentHandle.IsValid())
	{
		return TryActivateAbility(ActivateAbilityActionGroup.HitAbilityFragmentHandle.GameplayAbilitySpecHandle);
	}

	return false;	
}

bool UGASComponent::TryAttackAbilityFromActionGroup(int32 ElementIndex)
{
	if(ActivateAbilityActionGroup.AttackAbilityFragmentHandles.Num() <= ElementIndex
		|| false == ActivateAbilityActionGroup.AttackAbilityFragmentHandles[ElementIndex].IsValid())
	{
		return false;
	}
	
	if(TryActivateAbility(ActivateAbilityActionGroup.AttackAbilityFragmentHandles[ElementIndex].GameplayAbilitySpecHandle))
	{
		return true;
	}

	return false;
}

bool UGASComponent::CanGEExec(UAbilitySystemComponent* AbilitySystemComponent,
	UAbilitySystemComponent* TargetAbilitySystemComponent)
{
	if(false == Super::CanGEExec(AbilitySystemComponent, TargetAbilitySystemComponent))
	{
		return false;
	}

	if(TargetAbilitySystemComponent->HasMatchingGameplayTag(UAsadalGameplayTags::AvoidStateGameplayTag))
	{
		//회피중이였다.
		return false;
	}

	return true;
}

void UGASComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
}

bool UGASComponent::IsCriticalAbility()
{
	TArray<FGameplayAbilitySpec> ActivateGameplayAbilities = GetActivatableAbilities();

	for(const FGameplayAbilitySpec& ActivateGameplayAbilitySpec : ActivateGameplayAbilities)
	{
		UGameplayAbility* GameplayAbility = ActivateGameplayAbilitySpec.Ability;

		if(GameplayAbility->AbilityTags.HasTag(UAsadalGameplayTags::AttackActionGameplayTag))
		{
			for(UGameplayAbility* GameplayAbilityInstance : ActivateGameplayAbilitySpec.NonReplicatedInstances)
			{
				const UBaseGameplayAbility* BaseGameplayAbilityInstance = Cast<UBaseGameplayAbility>(GameplayAbilityInstance);

				if(IsValid(BaseGameplayAbilityInstance))
				{				
					const TArray<UKRGGEExecResult*>& ExecResults = BaseGameplayAbilityInstance->GetAbilityGEExecInfos();

					for(const UKRGGEExecResult* KRGExecResult : ExecResults)
					{
						const UGEExecResult* ExecResult = Cast<UGEExecResult>(KRGExecResult);
					
						if(ExecResult->IsCritical())
						{
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

void UGASComponent::OnUpdateActivateFragmentAbility()
{
	Super::OnUpdateActivateFragmentAbility();

	ActivateAbilityActionGroup.Clear();

	for(const FKRGGASFragmentAbilityHandle& KRGGASFragmentAbilityHandle : ActivateAbilityFragmentHandles)
	{
		FGameplayTag ActionTag;
		FGameplayTag AbilityTag;

		FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromHandle(KRGGASFragmentAbilityHandle.GameplayAbilitySpecHandle);

		if(nullptr != AbilitySpec)
		{	
			for(const FGameplayTag& GameplayTag : AbilitySpec->Ability->AbilityTags)
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
				if(UAsadalGameplayTags::AttackActionGameplayTag == ActionTag)
				{
					ActivateAbilityActionGroup.AttackAbilityFragmentHandles.Add(KRGGASFragmentAbilityHandle);
				}
				else if(UAsadalGameplayTags::HitActionGameplayTag == ActionTag)
				{
					ActivateAbilityActionGroup.HitAbilityFragmentHandle = KRGGASFragmentAbilityHandle;
				}
				else if(UAsadalGameplayTags::AvoidGameplayTag == ActionTag)
				{
					ActivateAbilityActionGroup.AvoidAbilityFragmentHandle = KRGGASFragmentAbilityHandle;
				}
			}			
		}
	}
}

void UGASComponent::OnUpdateActivateFragmentAttributeSet()
{
	Super::OnUpdateActivateFragmentAttributeSet();
}
