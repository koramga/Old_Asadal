// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "KRGGASFragment.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class KRGGASTOOLKIT_API UKRGGASFragment : public UObject
{
	GENERATED_BODY()

public :
	virtual bool IsValidFragment() const;
};
