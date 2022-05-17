// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"

#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"

// Sets default values
AMainGameMode::AMainGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMainGameMode::AddGameplayTag(const FGameplayTag& GameplayTag)
{
	GameplayTagContainer.AddTag(GameplayTag);
}

bool AMainGameMode::HasGameplayTag(const FGameplayTag& GameplayTag)
{
	return GameplayTagContainer.HasTag(GameplayTag);
}

void AMainGameMode::RemoveGameplayTag(const FGameplayTag& GameplayTag)
{
	GameplayTagContainer.RemoveTag(GameplayTag);
}

bool AMainGameMode::SetTimeDilationKeepTime(const FGameplayTag& GameplayTag,
	const FTimeDilationSettings& TimeDilationSettings)
{
	if(false == GameplayTag.MatchesTag(UAsadalGameplayTags::GameTimeDilationTag))
	{
		return false;
	}
	
	if(TimeDilationGameplayTag.GetTagName().IsNone())
	{
		int32 CurrentPriority = UAsadalGameplayTags::GetDilationPriority(TimeDilationGameplayTag);
		int32 InPriority = UAsadalGameplayTags::GetDilationPriority(GameplayTag);

		if(CurrentPriority > InPriority)
		{
			RemoveGameplayTag(TimeDilationGameplayTag);
			TimeDilationGameplayTag = FGameplayTag::EmptyTag;
		}
	}

	if(TimeDilationGameplayTag == FGameplayTag::EmptyTag)
	{
		TimeDilationKeepTime = TimeDilationSettings.KeepTime;
		TimeDilationTickTime = 0.f;
		TimeDilationGameplayTag = GameplayTag;
		AddGameplayTag(TimeDilationGameplayTag);
		GetWorld()->GetWorldSettings()->SetTimeDilation(TimeDilationSettings.TimeDilation);

		return true;
	}

	return false;
}

// Called when the game starts or when spawned
void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(FGameplayTag::EmptyTag != TimeDilationGameplayTag)
	{
		TimeDilationTickTime += DeltaTime / GetWorld()->GetWorldSettings()->TimeDilation;

		if(TimeDilationTickTime >= TimeDilationKeepTime)
		{
			RemoveGameplayTag(TimeDilationGameplayTag);
			TimeDilationGameplayTag = FGameplayTag::EmptyTag;
			GetWorld()->GetWorldSettings()->SetTimeDilation(1.f);
		}
	}
}

