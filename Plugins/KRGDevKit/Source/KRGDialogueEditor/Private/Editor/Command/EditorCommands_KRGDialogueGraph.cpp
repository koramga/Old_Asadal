#include "EditorCommands_KRGDialogueGraph.h"

#define LOCTEXT_NAMESPACE "EditorCommands_KRGDialogueGraph"

void FEditorCommands_KRGDialogueGraph::RegisterCommands()
{
	UI_COMMAND(GraphSettings, "Graph Settings", "Graph Settings", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(DockSettings, "Dock Settings", "Dock Setting", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
