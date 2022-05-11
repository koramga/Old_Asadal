// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "BaseEquipment.generated.h"

USTRUCT(BlueprintType)
struct ASADAL_API FEquipmentOverlapEventData
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<AActor> OtherActor;
	TSoftObjectPtr<class ABaseEquipment>	Caller;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquipmentOverlapEvent, FEquipmentOverlapEventData, OverlapEventData);

UCLASS()
class ASADAL_API ABaseEquipment : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseEquipment();

public :
	void SetEquip(bool bIsEquip);

	FOnEquipmentOverlapEvent OnEquipmentOverlapEvent;

	void SetActivateCollision(bool bIsActivate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	void OnEquipmentOverlapBroadcast(AActor* OtherActor);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	TArray<FString>		CollisionComponentNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	FGameplayTag		WeaponGameplayTag;

	TArray<TSoftObjectPtr<UPrimitiveComponent>>	CollisionComponents;
	TArray<AActor*>								AlreadyOverlapActors;

private :
	UFUNCTION()
	void __OnComponentOverlapNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};