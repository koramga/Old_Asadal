// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "Asadal/Widget/Screen/BaseScreenWidget.h"

// Sets default values
AMainGameMode::AMainGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(BaseScreenWidgetClass))
	{
		BaseScreenWidget = 	CreateWidget<UBaseScreenWidget>(GetWorld(), BaseScreenWidgetClass);
		
		if (BaseScreenWidget)
			BaseScreenWidget->AddToViewport();
	}	
}

// Called every frame
void AMainGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

