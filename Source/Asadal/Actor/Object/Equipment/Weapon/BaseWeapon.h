// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BaseEquipment.h"
#include "BaseWeapon.generated.h"


UCLASS()
class ASADAL_API ABaseWeapon : public ABaseEquipment
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseWeapon();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
