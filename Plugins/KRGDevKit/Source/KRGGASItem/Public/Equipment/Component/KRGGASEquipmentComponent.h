// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "KRGGASEquipmentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRGGASITEM_API UKRGGASEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKRGGASEquipmentComponent();

	
	void SetKRGAbilitySystemComponent(class UKRGAbilitySystemComponent* AbilitySystemComponent);
	TSoftObjectPtr<class UKRGGASEquipment> FindEquipmentFromItem(class UKRGGASItem* Item);
	TSoftObjectPtr<class UKRGGASEquipment> FindEquipmentFromGameplayTag(const FGameplayTag& GameplayTag);
	bool AddExtraItem(class UKRGGASItem* Item);
	bool EquipmentNextExtraItem(const FGameplayTag& EquipmentGameplayTag);
	bool EquipmentItem(class UKRGGASItem* Item);
	class UKRGGASItem* GetItemFromEquipmentGameplayTag(const FGameplayTag& GameplayTag) const;
	bool TakeoffItem(class UKRGGASItem* Item);
	bool AddDefinition(class UKRGGASDefinition* Definition);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Definition")
	TArray<UDataAsset*>									KRGGASEquipmentDefinitions;
	
	TArray<TSoftObjectPtr<class UKRGGASEquipment>>		KRGGASEquipments;
	TSoftObjectPtr<class UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
};
