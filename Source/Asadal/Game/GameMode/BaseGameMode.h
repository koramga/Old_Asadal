// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "BaseGameMode.generated.h"

UCLASS()
class ASADAL_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UBaseScreenWidget>	BaseScreenWidgetClass;
	
	TSoftObjectPtr<class UBaseScreenWidget>	BaseScreenWidget;
};
