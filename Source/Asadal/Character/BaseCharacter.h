// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../GAS/GASComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Asadal/Actor/Object/Equipment/BaseEquipment.h"
#include "MetaTools/VariableGroup/MaterialInstanceVariable.h"
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
	virtual void TryActivateEquipment(const FGameplayTag& GameplayTag, bool bIsActivate);
	virtual void SetEquipInventoryItem(TSoftObjectPtr<class UAsadalInventoryItemDefinition> InventoryItemDefinition);
	virtual void TryEquipNextWeapon();
	virtual void TryDash();
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
	virtual void OnHit(const FOnAttributeChangeData& Data);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BaseCharacter")
	UGASComponent* GASComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|DamageText")
	TArray<TSubclassOf<class ATextActor>>						DamageTextActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|DamageText")
	TArray<FString>												DamageTextSpawnComponentNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Equipment")
	TArray<TSubclassOf<class UAsadalInventoryItemDefinition>>		EquipmentWeaponItemDefinitionClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|SubAnimInstance")
	TMap<FGameplayTag, TSubclassOf<UAnimInstance>>		SubAnimInstanceClassMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Abilities")
	TArray<TSubclassOf<class UBaseGameplayAbility>>	AbilityClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|MaterialInstance")
	TArray<FMaterialInstanceVariable>				HitMaterialInstanceVairables;

	TArray<TSoftObjectPtr<class UAsadalInventoryItemDefinition>>	EquipmentWeaponItemDefinitions;
	TSoftObjectPtr<UAsadalInventoryItemDefinition>					EquipmentWepaonItemDefinition;

	TArray<TSoftObjectPtr<USceneComponent>>						DamageTextSpawnComponents;

	TSoftObjectPtr<const class UBaseCharacterAttributeSet>	BaseCharacterAttributeSet;
	TSoftObjectPtr<class UBaseAnimInstance>	BaseAnimInstance;
	float MoveBlendRatio = 1.f;	
	
private :
	void __OnHealthChangedNative(const FOnAttributeChangeData& Data);
	void __OnManaChangedNative(const FOnAttributeChangeData& Data);
	
private:
	UFUNCTION()
	void __OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData);

	UFUNCTION()
	void __OnGEToTargetLatentEventNative(const TArray<FGEToTargetEventItem>& LatentEventItem);

	UFUNCTION()
	void __OnTagUpdatedEventNative(const FGameplayTag& GameplayTag, bool bIsActivate);
};