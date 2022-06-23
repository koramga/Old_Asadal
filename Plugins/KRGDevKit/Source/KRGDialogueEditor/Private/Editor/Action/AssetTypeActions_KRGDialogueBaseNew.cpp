#include "AssetTypeActions_KRGDialogueBaseNew.h"
#include "Editor/AssetEditor_KRGDialogueGraph.h"
#include "Graph/KRGDialogueGraph.h"

FAssetTypeActions_KRGDialogueBaseNew::FAssetTypeActions_KRGDialogueBaseNew(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

FText FAssetTypeActions_KRGDialogueBaseNew::GetName() const
{
	return FText::FromString(TEXT("Automation Testing System Graph"));
}

FColor FAssetTypeActions_KRGDialogueBaseNew::GetTypeColor() const
{
	return FColor(129, 196, 115);
}

UClass* FAssetTypeActions_KRGDialogueBaseNew::GetSupportedClass() const
{
	return UKRGDialogueGraph::StaticClass();
}

void FAssetTypeActions_KRGDialogueBaseNew::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for(auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		if(UKRGDialogueGraph* Graph = Cast<UKRGDialogueGraph>(*ObjIt))
		{
			TSharedRef<FAssetEditor_KRGDialogueGraph> NewGraphEditor(new FAssetEditor_KRGDialogueGraph);
			NewGraphEditor->InitATSGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

uint32 FAssetTypeActions_KRGDialogueBaseNew::GetCategories()
{
	return MyAssetCategory;
}
