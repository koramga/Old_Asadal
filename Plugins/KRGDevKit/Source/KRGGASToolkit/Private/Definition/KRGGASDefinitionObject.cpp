// Fill out your copyright notice in the Description page of Project Settings.


#include "Definition/KRGGASDefinitionObject.h"

bool UKRGGASDefinitionObject::SetDefinition(UKRGGASDefinition* Definition)
{
	if(CanUpdateDefinition(Definition))
	{
		UpdateDefinition(Definition);

		return true;
	}	

	return false;
}

void UKRGGASDefinitionObject::SetKRGAbilitySystemComponent(UKRGAbilitySystemComponent* InKRGAbilitySystemComponent)
{
	KRGAbilitySystemComponent = InKRGAbilitySystemComponent;
}

void UKRGGASDefinitionObject::UpdateDefinition(UKRGGASDefinition* Definition)
{
	KRGGASDefinition = Definition;
}

bool UKRGGASDefinitionObject::CanUpdateDefinition(UKRGGASDefinition* Definition) const
{
	return true;
}