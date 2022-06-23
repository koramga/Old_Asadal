#pragma once

#include "CoreMinimal.h"
#include "Editor/AssetEditor_KRGDialogueGraph.h"

class FAssetEditor_ATSGraph;
class FExtender;
class FToolBarBuilder;

class FAssetEditorToolbar_KRGDialogue : public TSharedFromThis<FAssetEditorToolbar_KRGDialogue>
{
public :
	FAssetEditorToolbar_KRGDialogue(TSharedPtr<FAssetEditor_KRGDialogueGraph> InATSGraphEditor)
		: ATSGraphEditor(InATSGraphEditor) {}
	void AddATSGraphToolbar(TSharedPtr<FExtender> Extender);

private:
	void FillATSGraphToolbar(FToolBarBuilder& ToolBarBuilder);

protected :
	//Pointer back to the blueprint editor tool that owns us
	TWeakPtr<FAssetEditor_KRGDialogueGraph>	ATSGraphEditor;
};
