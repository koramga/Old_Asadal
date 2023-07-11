#pragma once

#include "CoreMinimal.h"
#include "EditorStyleSet.h"

class FEditorCommands_KRGDialogueGraph
	: public TCommands<FEditorCommands_KRGDialogueGraph>
{
public:
	/** Constructor */
	FEditorCommands_KRGDialogueGraph()
		: TCommands<FEditorCommands_KRGDialogueGraph>("ATSGraphEditor",  FText::FromString("ATS Graph Editor"), NAME_None, FEditorStyle::GetStyleSetName())
	{
	}
	
	TSharedPtr<FUICommandInfo> GraphSettings;
	TSharedPtr<FUICommandInfo> AutoArrange;
	TSharedPtr<FUICommandInfo> DockSettings;

	virtual void RegisterCommands() override;
};
