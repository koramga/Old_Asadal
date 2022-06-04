// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Inventory/KRGGASInventoryComponent.h"
#include "BaseInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ASADAL_API UBaseInventoryComponent : public UKRGGASInventoryComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Test")
	TArray<UDataAsset*>				ItemDefinitions;
};
