// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "GameFramework/Actor.h"
#include "MainGameMode.generated.h"

UCLASS()
class ASADAL_API AMainGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainGameMode();
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMainScreenWidget*	MainScreenWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
