// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NPCController.generated.h"

/**
 * 
 */
UCLASS()
class ASADAL_API ANPCController : public AAIController
{
	GENERATED_BODY()

public :
	ANPCController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
