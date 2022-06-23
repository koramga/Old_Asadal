// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "Modules/ModuleManager.h"

class FKRGDialogueEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);

private:
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
	EAssetTypeCategories::Type ATSGraphAssetCategoryBit;
	TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_ATSGraph;
};
