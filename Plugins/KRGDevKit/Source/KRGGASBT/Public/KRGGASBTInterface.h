// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/KRGGASBTComponent.h"
#include "UObject/Interface.h"
#include "KRGGASBTInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UKRGGASBTInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class KRGGASBT_API IKRGGASBTInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UKRGGASBTComponent* GetKRGGASBTComponent() const = 0;
};
