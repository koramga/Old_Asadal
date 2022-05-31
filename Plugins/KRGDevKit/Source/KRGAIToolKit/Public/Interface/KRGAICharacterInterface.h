// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definition/KRGAIDefinition.h"
#include "UObject/Interface.h"
#include "KRGAICharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UKRGAICharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KRGAITOOLKIT_API IKRGAICharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UKRGAIDefinition* GetKRGAIDefinition() const = 0;
};
