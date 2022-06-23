#include "AssetEditorToolbar_KRGDialogue.h"

#include "Editor/Command/EditorCommands_KRGDialogueGraph.h"

void FAssetEditorToolbar_KRGDialogue::AddATSGraphToolbar(TSharedPtr<FExtender> Extender)
{
	check(ATSGraphEditor.IsValid());
	TSharedPtr<FAssetEditor_KRGDialogueGraph> ATSEditorGraphPtr = ATSGraphEditor.Pin();

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension("Asset", EExtensionHook::After, ATSEditorGraphPtr->GetToolkitCommands(), FToolBarExtensionDelegate::CreateSP(this, &FAssetEditorToolbar_KRGDialogue::FillATSGraphToolbar));
	ATSEditorGraphPtr->AddToolbarExtender(ToolbarExtender);
}

void FAssetEditorToolbar_KRGDialogue::FillATSGraphToolbar(FToolBarBuilder& ToolBarBuilder)
{
	check(ATSGraphEditor.IsValid());
	TSharedPtr<FAssetEditor_KRGDialogueGraph> ATSGraphEditorPtr = ATSGraphEditor.Pin();

	//Stop
	ToolBarBuilder.BeginSection("ATSGraph");
	{
		ToolBarBuilder.AddToolBarButton(FEditorCommands_KRGDialogueGraph::Get().GraphSettings,
			NAME_None,
			FText::FromString("Graph Settings")
			, FText::FromString("Show the Graph Settings")
			, FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings"));
	}
	ToolBarBuilder.EndSection();

	ToolBarBuilder.BeginSection("Util");
	{
		ToolBarBuilder.AddToolBarButton(FEditorCommands_KRGDialogueGraph::Get().DockSettings,
			NAME_None,
			FText::FromString("Dock Settings")
			, FText::FromString("Show the Dock Settings")
			, FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.GameSettings"));		
	}
	ToolBarBuilder.EndSection();
}
