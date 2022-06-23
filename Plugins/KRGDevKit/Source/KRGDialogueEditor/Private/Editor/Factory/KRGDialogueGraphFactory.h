// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Graph/KRGDialogueGraph.h"

#include "KRGDialogueGraphFactory.generated.h"

/**
 * 
 */
UCLASS()
class KRGDIALOGUEEDITOR_API UKRGDialogueGraphFactory : public UFactory
{
	GENERATED_BODY()

public :
	UKRGDialogueGraphFactory();
	virtual ~UKRGDialogueGraphFactory();

	UPROPERTY(EditAnywhere, Category="DataAsset")
	TSubclassOf<UKRGDialogueGraph>	BaseGraphClass;

	virtual bool ConfigureProperties() override;
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
