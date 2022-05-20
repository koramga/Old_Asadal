// Fill out your copyright notice in the Description page of Project Settings.


#include "AsadalGameplayTags.h"

FGameplayTag const UAsadalGameplayTags::StateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State"));
FGameplayTag const UAsadalGameplayTags::AttackStateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Attack"));
FGameplayTag const UAsadalGameplayTags::HitStateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Hit"));
FGameplayTag const UAsadalGameplayTags::DeathStateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Death"));
FGameplayTag const UAsadalGameplayTags::InvincibleStateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Invincible"));
FGameplayTag const UAsadalGameplayTags::AvoidStateGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.State.Avoid"));
FGameplayTag const UAsadalGameplayTags::ActionGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Action"));
FGameplayTag const UAsadalGameplayTags::DeathActionGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Death"));
FGameplayTag const UAsadalGameplayTags::HitActionGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Hit"));
FGameplayTag const UAsadalGameplayTags::AttackActionGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Attack"));
FGameplayTag const UAsadalGameplayTags::AvoidGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Action.Avoid"));
FGameplayTag const UAsadalGameplayTags::AbilityGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability"));
FGameplayTag const UAsadalGameplayTags::AbilityOneHandAxeTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.OneHand.Axe"));
FGameplayTag const UAsadalGameplayTags::AbilityOneHandMaceTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.OneHand.Mace"));
FGameplayTag const UAsadalGameplayTags::AbilityOneHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.OneHand.Shield"));
FGameplayTag const UAsadalGameplayTags::AbilityOneHandSwordTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.OneHand.Sword"));
FGameplayTag const UAsadalGameplayTags::AbilityTwinHandBladeTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.TwinHand.Blade"));
FGameplayTag const UAsadalGameplayTags::AbilityTwinHandDaggerTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.TwinHand.Dagger"));
FGameplayTag const UAsadalGameplayTags::AbilityTwoHandGreatswordTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.TwoHand.Greatsword"));
FGameplayTag const UAsadalGameplayTags::AbilityTwoHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.TwoHand.Shield"));
FGameplayTag const UAsadalGameplayTags::BaseAbilityGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Ability.Base"));
FGameplayTag const UAsadalGameplayTags::EventAttackBasicTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.Basic"));
FGameplayTag const UAsadalGameplayTags::ItemWeaponTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon"));
FGameplayTag const UAsadalGameplayTags::ItemOneHandAxeTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.OneHand.Axe"));
FGameplayTag const UAsadalGameplayTags::ItemOneHandMaceTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.OneHand.Mace"));
FGameplayTag const UAsadalGameplayTags::ItemOneHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.OneHand.Shield"));
FGameplayTag const UAsadalGameplayTags::ItemOneHandSwordTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.OneHand.Sword"));
FGameplayTag const UAsadalGameplayTags::ItemTwinHandBladeTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.TwinHand.Blade"));
FGameplayTag const UAsadalGameplayTags::ItemTwinHandDaggerTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.TwinHand.Dagger"));
FGameplayTag const UAsadalGameplayTags::ItemTwoHandGreatswordTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.TwoHand.Greatsword"));
FGameplayTag const UAsadalGameplayTags::ItemTwoHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Item.Weapon.TwoHand.Shield"));
FGameplayTag const UAsadalGameplayTags::GameTimeDilationTag = FGameplayTag::RequestGameplayTag(TEXT("Game.TimeDilation"));
FGameplayTag const UAsadalGameplayTags::GameTimeDilationStrikeTag = FGameplayTag::RequestGameplayTag(TEXT("Game.TimeDilation.Strike"));

int32 UAsadalGameplayTags::GetDilationPriority(const FGameplayTag& GameplayTag)
{
	//Priority는 낮을 수록 높다. [Linux랑 동일]
	if(GameplayTag.MatchesTag(GameTimeDilationStrikeTag))
	{
		return 0;
	}

	return INT32_MAX;	
}

FGameplayTag UAsadalGameplayTags::GetAbilityGameplayTagFromItem(const FGameplayTag& ItemGameplayTag)
{
	if(ItemOneHandAxeTag == ItemGameplayTag)
	{
		return AbilityOneHandAxeTag;	
	}
	else if(ItemOneHandMaceTag == ItemGameplayTag)
	{
		return AbilityOneHandMaceTag;
	}
	else if(ItemOneHandShieldTag == ItemGameplayTag)
	{
		return AbilityOneHandShieldTag;
	}
	else if(ItemOneHandSwordTag == ItemGameplayTag)
	{
		return AbilityOneHandSwordTag;
	}
	else if(ItemTwinHandBladeTag == ItemGameplayTag)
	{
		return AbilityTwinHandBladeTag;
	}
	else if(ItemTwinHandDaggerTag == ItemGameplayTag)
	{
		return AbilityTwinHandDaggerTag;
	}
	else if(ItemTwoHandGreatswordTag == ItemGameplayTag)
	{
		return AbilityTwoHandGreatswordTag;
	}
	else if(ItemTwoHandShieldTag == ItemGameplayTag)
	{
		return AbilityTwoHandShieldTag;
	}

	return FGameplayTag::EmptyTag;
}
