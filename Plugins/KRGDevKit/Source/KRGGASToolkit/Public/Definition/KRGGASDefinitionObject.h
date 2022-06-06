// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KRGGASDefinition.h"
#include "GAS/KRGAbilitySystemComponent.h"
#include "UObject/Object.h"
#include "KRGGASDefinitionObject.generated.h"

/**
 * 
 */
UCLASS()
class KRGGASTOOLKIT_API UKRGGASDefinitionObject : public UObject
{
	GENERATED_BODY()

public :
	bool SetDefinition(UKRGGASDefinition* Definition);
	void SetKRGAbilitySystemComponent(UKRGAbilitySystemComponent* InKRGAbilitySystemComponent);

protected :
	template <typename T>
	bool HasFragment() const
	{
		if(KRGGASDefinition.IsValid()
			&& IsValid(KRGGASDefinition->FindFragment<T>()))
		{
			return true;
		}

		return false;
	}
	
	template <typename T>
	bool HasFragment(UKRGGASDefinition* Definition) const
	{
		if(IsValid(Definition->FindFragment<T>()))
		{
			return true;;
		}

		return false;
	}

protected:
	virtual void UpdateDefinition(UKRGGASDefinition* Definition);
	virtual bool CanUpdateDefinition(UKRGGASDefinition* Definition) const;
	
protected:
	TSoftObjectPtr<UKRGGASDefinition>				KRGGASDefinition;
	TSoftObjectPtr<UKRGAbilitySystemComponent>		KRGAbilitySystemComponent;
};
