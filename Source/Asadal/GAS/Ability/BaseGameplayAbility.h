// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "UObject/Object.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public :
	UTexture2D* GetIconTexture() const;
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	virtual void EndAbility(bool bWasCancelled = false, bool bReplicateEndAbility = true);

public :
	bool HasTagActivationRequiredTags(FGameplayTag GameplayTag);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	UTexture2D*	IconTexture;
	
};
