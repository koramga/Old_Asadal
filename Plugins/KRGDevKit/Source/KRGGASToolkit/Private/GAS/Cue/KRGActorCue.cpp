﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGGASToolkit/Public/GAS/Cue/KRGActorCue.h"


// Sets default values
AKRGActorCue::AKRGActorCue()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AKRGActorCue::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKRGActorCue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

