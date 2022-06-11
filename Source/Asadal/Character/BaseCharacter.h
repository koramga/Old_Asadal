// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "../GAS/GASComponent.h"
#include "Abilities/GameplayAbility.h"
#include "Asadal/Actor/Object/Equipment/BaseEquipment.h"
#include "Asadal/GAS/BT/BaseBTComponent.h"
#include "Asadal/GAS/Equipment/BaseEquipmentComponent.h"
#include "Asadal/GAS/Inventory/BaseInventoryComponent.h"
#include "KRGGASBT/Public/KRGGASBTInterface.h"
#include "MetaTools/VariableGroup/MaterialInstanceVariable.h"
#include "BaseCharacter.generated.h"

UCLASS()
class ASADAL_API ABaseCharacter : public ACharacter, public IAbilitySystemInterface, public IKRGGASBTInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UKRGGASBTComponent* GetKRGGASBTComponent() const override;
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
	UTexture2D* GetAbilityIconByIndex(int32 Index);

public :
	virtual void SetActivateCollision(const FString& Name, bool bIsActivate);
	virtual void TryActivateEquipment(const FGameplayTag& GameplayTag, bool bIsActivate);
	virtual void TryEquipNextWeapon();
	virtual void TryAvoid();
	virtual bool TryAttackAbilityByIndex(int32 Index);
	virtual void InputMoveForward(float Value);
	virtual void InputMoveRight(float Value);
	bool IsDeath() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;

protected:
	virtual void OnHealthChanged(const FOnAttributeChangeData& Data);
	virtual void OnManaChanged(const FOnAttributeChangeData& Data);
	virtual void OnDeath(bool bIsDeath);
	virtual void OnHit(const FOnAttributeChangeData& Data);
	virtual void OnTagUpdatedEvent(const FGameplayTag& GameplayTag, bool bIsActivate);
	virtual void OnUpdatePossessedByPlayer(class APCController* PCController);
	virtual void OnUpdatePossessedByAI(class ANPCController* NPCController);
	virtual void OnUpdateUnPossessed();

protected:
	void UpdateCharacterStatusWidget();
	bool IsPossessedByPlayer() const;
	bool IsPossessedByAI() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UGASComponent* GASComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseEquipmentComponent*	BaseEquipmentComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseInventoryComponent*	BaseInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBaseBTComponent*			BaseBTComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|DamageText")
	TArray<TSubclassOf<class ATextActor>>					DamageTextActorClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|DamageText")
	TArray<FString>											DamageTextSpawnComponentNames;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|SubAnimInstance")
	TMap<FGameplayTag, TSubclassOf<UAnimInstance>>			SubAnimInstanceClassMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|MaterialInstance")
	TArray<FMaterialInstanceVariable>						HitMaterialInstanceVairables;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Test")
	FGameplayTagContainer									AddLooseGameplayTagContainer;

	TSoftObjectPtr<class UScreenCharacterStatusWidget>			ScreenCharacterStatusWidget;
	TArray<TSoftObjectPtr<USceneComponent>>					DamageTextSpawnComponents;

	TSoftObjectPtr<const class UOffenseAttributeSet>		OffenseAttributeSet;
	TSoftObjectPtr<const class UDefenseAttributeSet>		DefenseAttributeSet;
	TSoftObjectPtr<const class ULifeAttributeSet>			LifeAttributeSet;
	TSoftObjectPtr<class UBaseAnimInstance>					BaseAnimInstance;
	float MoveBlendRatio = 1.f;
	
private :
	void __OnHealthChangedNative(const FOnAttributeChangeData& Data);
	void __OnManaChangedNative(const FOnAttributeChangeData& Data);
	
private:
	UFUNCTION()
	void __OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData);

	UFUNCTION()
	void __OnGEToTargetLatentEventNative(const TArray<FGEEExecEvent>& GEExecEvents, bool bIsCritical);

	UFUNCTION()
	void __OnTagUpdatedEventNative(const FGameplayTag& GameplayTag, bool bIsActivate);
};