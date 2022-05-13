// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../GAS/GASComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Asadal/Actor/Object/Equipment/BaseEquipment.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ASADAL_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	FGameplayAbilitySpecHandle InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel);
	void GetHealthValues(float& Health, float& MaxHealth);
	void SetHealthValues(float NewHealth, float NewMaxHealth);
	void GetManaValues(float& Mana, float& MaxMana);
	void SetManaValues(float NewMana, float NewMaxMana);
	void ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewAbilityLevel);
	void CancelAbilityWithTags(FGameplayTagContainer WithTags, FGameplayTagContainer WithoutTags);
	void AddLooseGameplayTag(FGameplayTag TagToAdd);
	bool HasMatchingGameplayTag(FGameplayTag Tag) const;
	void RemoveLooseGameplayTag(FGameplayTag TagToRemove);
	void ApplyGEToTargetData(const FGameplayEffectSpecHandle& GESpec, const FGameplayAbilityTargetDataHandle& TargetDataHandle);
	void LinkSubAnimInstance(const FGameplayTag& GameplayTag);
	void UnLinkSubAnimInstance(const FGameplayTag& GameplayTag);

public :
	virtual void SetActivateCollision(const FString& Name, bool bIsActivate);
	virtual void SetActivateEquipment(FGameplayTag GameplayTag, bool bIsActivate);
	void SetupWeapons();
	bool IsDeath() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void UpdateDeath(bool bIsDeath);

protected:
	void SetEquipWepaon(bool bIsEquip);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	UGASComponent* GASComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	TArray<TSubclassOf<class ATextActor>>		DamageTextActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	TArray<FString>								DamageTextSpawnComponentNames;

	TSoftObjectPtr<const class UBaseCharacterAttributeSet>	BaseCharacterAttributeSet;
	TSoftObjectPtr<class UBaseAnimInstance>	BaseAnimInstance;
	float MoveBlendRatio = 1.f;

	TArray<TSoftObjectPtr<UChildActorComponent>>	BaseWeapons;
	

	TArray<TSoftObjectPtr<USceneComponent>>			DamageTextSpawnComponents;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|SubAnimInstance")
	TMap<FGameplayTag, TSubclassOf<UAnimInstance>>		SubAnimInstanceClassMap;

//private:
//	UFUNCTION()
//	virtual void __OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData);
	
private :
	void __OnHealthChangedNative(const FOnAttributeChangeData& Data);
	void __OnManaChangedNative(const FOnAttributeChangeData& Data);
};
