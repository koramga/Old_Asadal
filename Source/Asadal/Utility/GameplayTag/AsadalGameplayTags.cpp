﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "AsadalGameplayTags.h"

FGameplayTag const UAsadalGameplayTags::DeathGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Status.Death"));
FGameplayTag const UAsadalGameplayTags::EventAttackBasicTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.Basic"));
FGameplayTag const UAsadalGameplayTags::ObjectWeaponTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon"));
FGameplayTag const UAsadalGameplayTags::OneHandAxeTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.OneHand.Axe"));
FGameplayTag const UAsadalGameplayTags::OneHandMaceTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.OneHand.Mace"));
FGameplayTag const UAsadalGameplayTags::OneHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.OneHand.Shield"));
FGameplayTag const UAsadalGameplayTags::OneHandSwordTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.OneHand.Sword"));
FGameplayTag const UAsadalGameplayTags::TwinHandBladeTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.TwinHand.Blade"));
FGameplayTag const UAsadalGameplayTags::TwinHandDaggerTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.TwinHand.Dagger"));
FGameplayTag const UAsadalGameplayTags::TwoHandGreatswordTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.TwoHand.Greatsword"));
FGameplayTag const UAsadalGameplayTags::TwoHandShieldTag = FGameplayTag::RequestGameplayTag(TEXT("Object.Weapon.TwoHand.Shield"));