// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Actor/BaseObject.h"
#include "Asadal/Asadal.h"
#include "BaseWeapon.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBaseWeaponOverlapBeginEvent, FOverlapEventData, OverlapEventData);

UCLASS()
class ASADAL_API ABaseWeapon : public ABaseObject
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();

	FOnBaseWeaponOverlapBeginEvent OnBaseWeaponOverlapBeginEvent;

	void SetActivateCollision(bool bIsActivate);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup")
	TArray<FString>		CollisionComponentNames;

	TArray<TSoftObjectPtr<UPrimitiveComponent>>	CollisionComponents;

private :
	UFUNCTION()
	void __OnComponentOverlapNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
