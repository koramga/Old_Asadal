﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Asadal/Actor/BaseActor.h"
#include "GameFramework/Actor.h"
#include "BaseObject.generated.h"

UCLASS()
class ASADAL_API ABaseObject : public ABaseActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
