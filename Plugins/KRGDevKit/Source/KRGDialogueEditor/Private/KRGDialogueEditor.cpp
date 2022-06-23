// Copyright Epic Games, Inc. All Rights Reserved.

#include "KRGDialogueEditor.h"

#include "AssetToolsModule.h"
#include "Editor/Action/AssetTypeActions_KRGDialogueBaseNew.h"
#include "Editor/Factory/KRGDialogueElementFactory.h"
#include "Editor/Style/KRGDialogueEditorStyle.h"

#define LOCTEXT_NAMESPACE "FKRGDialogueEditorModule"

void FKRGDialogueEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FKRGDialogueEditorStyle::Initialize();
	
	GraphPanelNodeFactory_ATSGraph = MakeShareable(new FKRGDialogueElementFactory);
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_ATSGraph);
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	ATSGraphAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("DialogueGraph")), LOCTEXT("KRGDialogueGraphAssetCategory", "DialogueGraph"));
	
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_KRGDialogueBaseNew(ATSGraphAssetCategoryBit)));
}

void FKRGDialogueEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	// Unregister all the asset types that we registered
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();
		for (int32 Index = 0; Index < CreatedAssetTypeActions.Num(); ++Index)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeActions[Index].ToSharedRef());
		}
	}

	if (GraphPanelNodeFactory_ATSGraph.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualNodeFactory(GraphPanelNodeFactory_ATSGraph);
		GraphPanelNodeFactory_ATSGraph.Reset();
	}

	FKRGDialogueEditorStyle::Shutdown();
}

void FKRGDialogueEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FKRGDialogueEditorModule, KRGDialogueEditor)