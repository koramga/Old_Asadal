// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Fragment/KRGGASFragment_EquipableItem.h"
#include "GameFramework/Character.h"
#include "GAS/KRGAbilitySystemComponent.h"

const TArray<FKRGEquipmentItemFragmentDefinition>& UKRGGASFragment_EquipableItem::GetEquipmentItemDefinitions() const
{
	return EquipmentItemDefinitions;
}

TSubclassOf<UGameplayEffect> UKRGGASFragment_EquipableItem::GetGameplayEffectClass() const
{
	return GameplayEffectClass;
}
