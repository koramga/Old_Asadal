#pragma once
#include "Graph/KRGDialogueGraph.h"
#include "Settings/KRGDialogueEditorSettings.h"

class FAssetEditor_KRGDialogueGraph
	: public FAssetEditorToolkit, public FNotifyHook, public FGCObject
{
public :
	FAssetEditor_KRGDialogueGraph();
	virtual ~FAssetEditor_KRGDialogueGraph();

	void InitATSGraphAssetEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UKRGDialogueGraph* Graph);

	//IToolkit interface
		virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	//End of IToolkit interface

	//FassetEditorToolkit
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FText GetToolkitName() const override;
	virtual FText GetToolkitToolTipText() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FString GetDocumentationLink() const override;
	virtual void SaveAsset_Execute() override;
	//End of FAssetToolkit

	//Toolbar
	TSharedPtr<class FAssetEditorToolbar_ATSBase> GetToolbarBuilder() { return ToolbarBuilder; }
	void RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager);

	//FSerializableObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	//End of FSerializableObject interface

	UKRGDialogueEditorSettings* GetSettings() const;

protected:
	TSharedRef<SDockTab> SpawnTab_Viewport(const FSpawnTabArgs& Args);
	//TSharedRef<SDockTab> SpawnTab_Details(const FSpawnTabArgs& Args);
	//TSharedRef<SDockTab> SpawnTab_EditorSettings(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTab_ATSDetails(const FSpawnTabArgs& Args);

	void CreateInternalWidgets();
	TSharedRef<SGraphEditor> CreateViewportWidget();

	void BindCommands();
	void CreateEdGraph();
	void CreateCommandList();
	TSharedPtr<SGraphEditor> GetCurrGraphEditor() const;
	FGraphPanelSelectionSet GetSelectedNodes() const;

	void RebuildGraph();

	//Delegates for graph editor commands
	void SelectAllNodes();
	bool CanSelectAllNodes();
	void DeleteSelectedNodes();
	bool CanDeleteNodes();
	void DeleteSelectedDuplicatableNodes();
	void CutSelectedNodes();
	bool CanCutNodes();
	void CopySelectedNodes();
	bool CanCopyNodes();
	void PasteNodes();
	void PasteNodesHere(const FVector2D& Location);
	bool CanPasteNodes();
	void DuplicateNodes();
	bool CanDuplicateNodes();

	void GraphSettings();
	bool CanGraphSettings() const;

	void DockSettings();
	bool CanDockSettings() const;

	void OnRenameNode();
	bool CanRenameNodes() const;

	////////////////////////////
	///Graph Editor Event
	void OnSelectedNodesChanged(const TSet<UObject*>& NewSelection);
	void OnNodeDoubleClicked(UEdGraphNode* Node);
	void OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent);
	void OnPackageSaved(const FString& PackageFileName, UObject* Outer);

protected:
	UKRGDialogueEditorSettings* ATSGraphEditorSettings;
	UKRGDialogueGraph* EditingGraph;

	//Toolbar
	TSharedPtr<class FAssetEditorToolbar_KRGDialogue> ToolbarBuilder;

	/**Handle to the registered OnPackageSave delegate */
	FDelegateHandle OnPackageSavedDelegateHandle;

	TSharedPtr<SGraphEditor> ViewportWidget;
	TSharedPtr<class SATSGraphNodeDetailWidget> ATSDetailWidget;

	/** The command list for this editor */
	TSharedPtr<FUICommandList> GraphEditorCommands;
};
