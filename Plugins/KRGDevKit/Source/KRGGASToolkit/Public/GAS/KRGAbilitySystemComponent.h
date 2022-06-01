// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "KRGAbilitySystemComponent.generated.h"

USTRUCT()
struct FGEEExecEvent
{
	GENERATED_BODY()

	TSoftObjectPtr<AActor>					Actor;
	TSoftObjectPtr<UAbilitySystemComponent>	AbilitySystemComponent;
	FGameplayTag							EventTag = FGameplayTag::EmptyTag;

	FGEEExecEvent() {}

	FGEEExecEvent(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag& EventTag)
		: Actor(AbilitySystemComponent->GetOwner()), AbilitySystemComponent(AbilitySystemComponent), EventTag(EventTag) {}
	
};

//struct FKRGAbilitySpec
//{
//	TArray<FGameplayAbilitySpecHandle>	AttackAbilitiesSpecHandles;
//	FGameplayAbilitySpecHandle			HitAbilitySpecHandle;
//	FGameplayAbilitySpecHandle			AvoidAbilitySpecHandle;
//	int32 AttackElementIndex = -1;
//};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGEExecLatentEvent, const TArray<FGEEExecEvent>&, LatentEventItems, bool, bIsCritical);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnTagUpdatedEvent, const FGameplayTag&, Tag, bool, TagExists);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRGGASTOOLKIT_API UKRGAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKRGAbilitySystemComponent();

public :
	virtual bool CanGEExec(UAbilitySystemComponent* AbilitySystemComponent, UAbilitySystemComponent* TargetAbilitySystemComponent);
	bool GEExecToTarget(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayTag& EventTag);
	void SetGEExecLatent(bool InIsLatentGEExec);

public :
	//We need to update for it.
	virtual bool IsCriticalAbility();
	
public :
	FOnGEExecLatentEvent		OnGEExecLatentEvent;
	FOnTagUpdatedEvent			OnTagUpdatedEvent;

protected:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnTagUpdated(const FGameplayTag& Tag, bool TagExists) override;

protected:
	TArray<FGEEExecEvent>		GEExecEvents;
	bool						bIsLatentGEExec = false;

	//TMap<FGameplayTag, FKRGAbilitySpec>	KRGAbilitySpecMap;
	//FKRGAbilitySpec*					ActivateKRGAbilitySpec;
};
