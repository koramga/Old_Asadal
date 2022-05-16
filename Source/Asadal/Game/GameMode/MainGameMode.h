// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseGameMode.h"
#include "GameplayTagContainer.h"
#include "Asadal/AsadalStructure.h"
#include "GameFramework/Actor.h"
#include "MainGameMode.generated.h"

UCLASS()
class ASADAL_API AMainGameMode : public ABaseGameMode
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMainGameMode();
	
public :
	void AddGameplayTag(const FGameplayTag& GameplayTag);
	bool HasGameplayTag(const FGameplayTag& GameplayTag);
	void RemoveGameplayTag(const FGameplayTag& GameplayTag);

public :
	bool SetTimeDilationKeepTime(const FGameplayTag& GameplayTag, const FTimeDilationSettings& TimeDilationSettings);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	FGameplayTagContainer	GameplayTagContainer;

	//TimeDilation
	FGameplayTag			TimeDilationGameplayTag = FGameplayTag::EmptyTag;
	float					TimeDilationKeepTime;
	float					TimeDilationTickTime;
};
