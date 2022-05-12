// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Character/BaseCharacter.h"
#include "GameFramework/Character.h"
#include "PCCharacter.generated.h"

UCLASS()
class ASADAL_API APCCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APCCharacter();

public :
	void InputMoveForward(float Value);
	void InputMoveRight(float Value);

public :
	FGameplayAbilitySpec* GetPCSkillAbilitySpecByIndex(int32 Index);
	bool TryActivateSkillByIndex(int32 Index);
	virtual void SetActivateEquipment(FGameplayTag GameplayTag, bool bIsActivate) override;
	void SetEquipInventoryItem(TSoftObjectPtr<class UAsadalInventoryItemDefinition> InventoryItemDefinition);
	void TryEquipNextWeapon();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected :
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;

	const TArray<FGameplayAbilitySpecHandle>*				PlayerSkillSet = nullptr;

	TMap<FGameplayTag, TArray<FGameplayAbilitySpecHandle>>	PlayerSkillSetOnWeapons;

	TArray<TSoftObjectPtr<class UAsadalInventoryItemDefinition>>	EquipmentWeaponItemDefinitions;
	TSoftObjectPtr<UAsadalInventoryItemDefinition>					EquipmentWepaonItemDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Temp")
	TArray<TSubclassOf<class UAsadalInventoryItemDefinition>>		EquipmentWeaponItemDefinitionClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Temp")
	TArray<TSubclassOf<class UBaseGameplayAbility>>	PlayerSkillAbilityClasses;
	
private:
	UFUNCTION()
	void __OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData);
};
