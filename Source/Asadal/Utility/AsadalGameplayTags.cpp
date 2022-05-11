// Fill out your copyright notice in the Description page of Project Settings.


#include "AsadalGameplayTags.h"

FGameplayTag const UAsadalGameplayTags::DeathGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Character.Status.Death"));
FGameplayTag const UAsadalGameplayTags::EventAttackBasicTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.Basic"));
