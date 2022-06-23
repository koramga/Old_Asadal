#include "AssetEditor_KRGDialogueGraph.h"

#include "EdGraphUtilities.h"
#include "GraphEditorActions.h"
#include "KRGDialogueEditorPCH.h"
#include "Command/EditorCommands_KRGDialogueGraph.h"
#include "Graph/EdKRGDialogueGraph.h"
#include "Toolbar/AssetEditorToolbar_KRGDialogue.h"
#include "Framework/Commands/GenericCommands.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Node/Edge/EdKRGDialogueEdge.h"
#include "Node/Node/EdKRGDialogueNode.h"
#include "Windows/WindowsPlatformApplicationMisc.h"
#include "Schema/EdGraphSchema_KRGDialogue.h"

const FName ATSGraphEditorAppName = FName(TEXT("ATSGraphEditorAppName"));

struct FATSGraphAssetEditorTabs
{
	//Tab identifiers
	static const FName ViewportID;
	static const FName ATSPropertyID;
};

const FName FATSGraphAssetEditorTabs::ViewportID(TEXT("Viewport"));
const FName FATSGraphAssetEditorTabs::ATSPropertyID(TEXT("ATSPropertyID"));

FAssetEditor_KRGDialogueGraph::FAssetEditor_KRGDialogueGraph()
{
	EditingGraph = nullptr;

	ATSGraphEditorSettings = NewObject<UKRGDialogueEditorSettings>(UKRGDialogueEditorSettings::StaticClass());

	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FAssetEditor_KRGDialogueGraph::OnPackageSaved);
}

FAssetEditor_KRGDialogueGraph::~FAssetEditor_KRGDialogueGraph()
{
	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);
}

void FAssetEditor_KRGDialogueGraph::InitATSGraphAssetEditor(const EToolkitMode::Type Mode,
	const TSharedPtr<IToolkitHost>& InitToolkitHost, UKRGDialogueGraph* Graph)
{
	EditingGraph = Graph;
	CreateEdGraph();

	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	FEditorCommands_KRGDialogueGraph::Register();

	if(!ToolbarBuilder.IsValid())
	{
		ToolbarBuilder = MakeShareable(new FAssetEditorToolbar_KRGDialogue(SharedThis(this)));
	}

	BindCommands();

	CreateInternalWidgets();

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);

	ToolbarBuilder->AddATSGraphToolbar(ToolbarExtender);

	//Layout
	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_ATSGraphEditor_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)->SetSizeCoefficient(0.9f)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.65f)
					->AddTab(FATSGraphAssetEditorTabs::ViewportID, ETabState::OpenedTab)->SetHideTabWell(true)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(1.f)
						->AddTab(FATSGraphAssetEditorTabs::ATSPropertyID, ETabState::OpenedTab)->SetHideTabWell(true)
					)
				)
			)
		);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	FAssetEditorToolkit::InitAssetEditor(Mode, InitToolkitHost, ATSGraphEditorAppName, StandaloneDefaultLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, EditingGraph, false);

	RegenerateMenusAndToolbars();
}

void FAssetEditor_KRGDialogueGraph::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(FText::FromString(TEXT("ATS Graph Editor")));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(FATSGraphAssetEditorTabs::ViewportID, FOnSpawnTab::CreateSP(this, &FAssetEditor_KRGDialogueGraph::SpawnTab_Viewport))
		.SetDisplayName(FText::FromString("Viewport"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "GraphEditor.EventGraph_16x"));

	InTabManager->RegisterTabSpawner(FATSGraphAssetEditorTabs::ATSPropertyID, FOnSpawnTab::CreateSP(this, &FAssetEditor_KRGDialogueGraph::SpawnTab_ATSDetails))
		.SetDisplayName(FText::FromString(TEXT("Property")))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Details"));

	//FAssetEditorToolkit::RegisterTabSpawners(TabManager);
}

void FAssetEditor_KRGDialogueGraph::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	//FAssetEditorToolkit::UnregisterTabSpawners(TabManager);

	InTabManager->UnregisterTabSpawner(FATSGraphAssetEditorTabs::ViewportID);
	InTabManager->UnregisterTabSpawner(FATSGraphAssetEditorTabs::ATSPropertyID);
}

FName FAssetEditor_KRGDialogueGraph::GetToolkitFName() const
{
	return FName("FATSGraphEditor");
}

FText FAssetEditor_KRGDialogueGraph::GetBaseToolkitName() const
{
	return FText::FromString(TEXT("ATS Graph Editor"));
}

FText FAssetEditor_KRGDialogueGraph::GetToolkitName() const
{
	if(EditingGraph->GetName() == "")
	{
		return FAssetEditorToolkit::GetToolkitName();
	}
	else
	{
		const bool bDirtyState = EditingGraph->GetOutermost()->IsDirty();

		FFormatNamedArguments Args;
		Args.Add(TEXT("GraphName"), FText::FromString(EditingGraph->GetName()));
		Args.Add(TEXT("DirtyState"), bDirtyState ? FText::FromString(TEXT("*")) : FText::GetEmpty());

		return FText::Format(FText::FromString("{GraphName}{DirtyState}"), Args);		
	}	
}

FText FAssetEditor_KRGDialogueGraph::GetToolkitToolTipText() const
{
	return FAssetEditorToolkit::GetToolTipTextForObject(EditingGraph); 
}

FLinearColor FAssetEditor_KRGDialogueGraph::GetWorldCentricTabColorScale() const
{
	return FLinearColor::White;
}

FString FAssetEditor_KRGDialogueGraph::GetWorldCentricTabPrefix() const
{
	return TEXT("AutomationTestingGraphEditor");
}

FString FAssetEditor_KRGDialogueGraph::GetDocumentationLink() const
{
	return TEXT("");
}

void FAssetEditor_KRGDialogueGraph::SaveAsset_Execute()
{
	if(EditingGraph != nullptr)
	{
		RebuildGraph();
	}
	
	FAssetEditorToolkit::SaveAsset_Execute();
}

void FAssetEditor_KRGDialogueGraph::RegisterToolbarTab(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

void FAssetEditor_KRGDialogueGraph::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(EditingGraph);
	Collector.AddReferencedObject(EditingGraph->EdGraph);
}

UKRGDialogueEditorSettings* FAssetEditor_KRGDialogueGraph::GetSettings() const
{
	return ATSGraphEditorSettings;
}

TSharedRef<SDockTab> FAssetEditor_KRGDialogueGraph::SpawnTab_Viewport(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == FATSGraphAssetEditorTabs::ViewportID);

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.Label(FText::FromString(TEXT("Viewport")));

	if(ViewportWidget.IsValid())
	{
		SpawnedTab->SetContent(ViewportWidget.ToSharedRef());
	}

	return SpawnedTab;
}

TSharedRef<SDockTab> FAssetEditor_KRGDialogueGraph::SpawnTab_ATSDetails(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == FATSGraphAssetEditorTabs::ATSPropertyID);

	return SNew(SDockTab);
	
	//return SNew(SDockTab)
	//	.Icon(FEditorStyle::GetBrush("LevelEditor.Tabs.Details"))
	//	.Label(FText::FromString(TEXT("Details")))
	//[
	//	ATSDetailWidget.ToSharedRef()
	//];
}

void FAssetEditor_KRGDialogueGraph::CreateInternalWidgets()
{
	ViewportWidget = CreateViewportWidget();

	FDetailsViewArgs Args;
	Args.bHideSelectionTip = true;
	Args.NotifyHook = this;

	//SAssignNew(ATSDetailWidget, SATSGraphNodeDetailWidget);
}

TSharedRef<SGraphEditor> FAssetEditor_KRGDialogueGraph::CreateViewportWidget()
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString(TEXT("ATSGraph"));

	CreateCommandList();

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FAssetEditor_KRGDialogueGraph::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FAssetEditor_KRGDialogueGraph::OnNodeDoubleClicked);

	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(true)
		.Appearance(AppearanceInfo)
		.GraphToEdit(EditingGraph->EdGraph)
		.GraphEvents(InEvents)
		.AutoExpandActionMenu(true)
		.ShowGraphStateOverlay(false);
}

void FAssetEditor_KRGDialogueGraph::BindCommands()
{
	ToolkitCommands->MapAction(FEditorCommands_KRGDialogueGraph::Get().GraphSettings,
		FExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::GraphSettings),
		FCanExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::CanGraphSettings)
		);
	ToolkitCommands->MapAction(FEditorCommands_KRGDialogueGraph::Get().DockSettings,
		FExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::DockSettings),
		FCanExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::CanDockSettings)
	);
}

void FAssetEditor_KRGDialogueGraph::CreateEdGraph()
{
	if(EditingGraph->EdGraph == nullptr)
	{		
		EditingGraph->EdGraph = CastChecked<UEdKRGDialogueGraph>(FBlueprintEditorUtils::CreateNewGraph(EditingGraph, NAME_None, UEdKRGDialogueGraph::StaticClass(), UEdGraphSchema_KRGDialogue::StaticClass()));
		EditingGraph->EdGraph->bAllowDeletion = false;

		//Give the schema a chance to fill out any reqquired nodes (like the results node)
		const UEdGraphSchema* Schema = EditingGraph->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*EditingGraph->EdGraph);

		//RootNode는 자동으로 추가한다.
		//FEdGraphSchemaAction_ATSBaseNew Action;
		//Action.CreateNodeTemplate(EditingGraph, EditingGraph->EdGraph, UEdGraphNode_ATSGeneralNode::StaticClass(), UATSRootNode::StaticClass());
		//Action.PerformAction(EditingGraph->EdGraph, nullptr, FVector2D(0.f, 0.f), false);
	}
}

void FAssetEditor_KRGDialogueGraph::CreateCommandList()
{
	if (GraphEditorCommands.IsValid())
	{
		return;
	}

	GraphEditorCommands = MakeShareable(new FUICommandList);

	// Can't use CreateSP here because derived editor are already implementing TSharedFromThis<FAssetEditorToolkit>
	// however it should be safe, since commands are being used only within this editor
	// if it ever crashes, this function will have to go away and be reimplemented in each derived class

	GraphEditorCommands->MapAction(FEditorCommands_KRGDialogueGraph::Get().GraphSettings,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::GraphSettings),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanGraphSettings));

	GraphEditorCommands->MapAction(FGenericCommands::Get().SelectAll,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::SelectAllNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanSelectAllNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Delete,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::DeleteSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanDeleteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Copy,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CopySelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanCopyNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Cut,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CutSelectedNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanCutNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Paste,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::PasteNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanPasteNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Duplicate,
		FExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::DuplicateNodes),
		FCanExecuteAction::CreateRaw(this, &FAssetEditor_KRGDialogueGraph::CanDuplicateNodes)
	);

	GraphEditorCommands->MapAction(FGenericCommands::Get().Rename,
		FExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::OnRenameNode),
		FCanExecuteAction::CreateSP(this, &FAssetEditor_KRGDialogueGraph::CanRenameNodes)
	);
}

TSharedPtr<SGraphEditor> FAssetEditor_KRGDialogueGraph::GetCurrGraphEditor() const
{
	return ViewportWidget;
}

FGraphPanelSelectionSet FAssetEditor_KRGDialogueGraph::GetSelectedNodes() const
{
	FGraphPanelSelectionSet CurrentSelection;
	TSharedPtr<SGraphEditor> FocusedGraphEd = GetCurrGraphEditor();

	if(FocusedGraphEd.IsValid())
	{
		CurrentSelection = FocusedGraphEd->GetSelectedNodes();
	}

	return CurrentSelection;
}

void FAssetEditor_KRGDialogueGraph::RebuildGraph()
{
	if(EditingGraph == nullptr)
	{
		LOG_WARNING(TEXT("FAssetEditor_KRGDialogueGraph::RebuildGraph Graph is nullptr"));
		return;
	}

	UEdKRGDialogueGraph* EdGraph = Cast<UEdKRGDialogueGraph>(EditingGraph->EdGraph);
	check(EdGraph != nullptr);

	EdGraph->RebuildGraph(this);
}

void FAssetEditor_KRGDialogueGraph::SelectAllNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if(CurrentGraphEditor.IsValid())
	{
		CurrentGraphEditor->SelectAllNodes();
	}
}

bool FAssetEditor_KRGDialogueGraph::CanSelectAllNodes()
{
	return true;
}

void FAssetEditor_KRGDialogueGraph::DeleteSelectedNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}

	const FScopedTransaction Transaction(FGenericCommands::Get().Delete->GetDescription());

	CurrentGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
	{
		UEdGraphNode* EdNode = Cast<UEdGraphNode>(*NodeIt);
		if (EdNode == nullptr || !EdNode->CanUserDeleteNode())
			continue;;

		if (UEdKRGDialogueNode* EdNode_Node = Cast<UEdKRGDialogueNode>(EdNode))
		{
			EdNode_Node->Modify();

			const UEdGraphSchema* Schema = EdNode_Node->GetSchema();
			if (Schema != nullptr)
			{
				Schema->BreakNodeLinks(*EdNode_Node);
			}

			EdNode_Node->DestroyNode();
		}
		else
		{
			EdNode->Modify();
			EdNode->DestroyNode();
		}
	}
}

bool FAssetEditor_KRGDialogueGraph::CanDeleteNodes()
{
	// If any of the nodes can be deleted then we should allow deleting
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node != nullptr && Node->CanUserDeleteNode())
		{
			return true;
		}
	}

	return false;
}

void FAssetEditor_KRGDialogueGraph::DeleteSelectedDuplicatableNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}

	const FGraphPanelSelectionSet OldSelectedNodes = CurrentGraphEditor->GetSelectedNodes();
	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}

	// Delete the duplicatable nodes
	DeleteSelectedNodes();

	CurrentGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(OldSelectedNodes); SelectedIter; ++SelectedIter)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter))
		{
			CurrentGraphEditor->SetNodeSelection(Node, true);
		}
	}
}

void FAssetEditor_KRGDialogueGraph::CutSelectedNodes()
{
	CopySelectedNodes();
	DeleteSelectedDuplicatableNodes();
}

bool FAssetEditor_KRGDialogueGraph::CanCutNodes()
{
	return CanCopyNodes() && CanDeleteNodes();
}

void FAssetEditor_KRGDialogueGraph::CopySelectedNodes()
{
	// Export the selected nodes and place the text on the clipboard
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();

	FString ExportedText;

	for (FGraphPanelSelectionSet::TIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node == nullptr)
		{
			SelectedIter.RemoveCurrent();
			continue;
		}

		if (UEdKRGDialogueEdge* EdNode_Edge = Cast<UEdKRGDialogueEdge>(*SelectedIter))
		{
			UEdKRGDialogueNode* EdStartNode = EdNode_Edge->GetEdStartNode();
			UEdKRGDialogueNode* EdEndNode = EdNode_Edge->GetEdEndNode();

			if (!SelectedNodes.Contains(EdStartNode) || !SelectedNodes.Contains(EdEndNode))
			{
				SelectedIter.RemoveCurrent();
				continue;
			}
		}

		Node->PrepareForCopying();
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);
}

bool FAssetEditor_KRGDialogueGraph::CanCopyNodes()
{
	// If any of the nodes can be duplicated then we should allow copying
	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	for (FGraphPanelSelectionSet::TConstIterator SelectedIter(SelectedNodes); SelectedIter; ++SelectedIter)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*SelectedIter);
		if (Node && Node->CanDuplicateNode())
		{
			return true;
		}
	}

	return false;
}

void FAssetEditor_KRGDialogueGraph::PasteNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (CurrentGraphEditor.IsValid())
	{
		PasteNodesHere(CurrentGraphEditor->GetPasteLocation());
	}
}

void FAssetEditor_KRGDialogueGraph::PasteNodesHere(const FVector2D& Location)
{
	// Find the graph editor with focus
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return;
	}
	// Select the newly pasted stuff
	UEdGraph* EdGraph = CurrentGraphEditor->GetCurrentGraph();

	{
		const FScopedTransaction Transaction(FGenericCommands::Get().Paste->GetDescription());
		EdGraph->Modify();

		// Clear the selection set (newly pasted stuff will be selected)
		CurrentGraphEditor->ClearSelectionSet();

		// Grab the text to paste from the clipboard.
		FString TextToImport;
		FPlatformApplicationMisc::ClipboardPaste(TextToImport);

		// Import the nodes
		TSet<UEdGraphNode*> PastedNodes;
		FEdGraphUtilities::ImportNodesFromText(EdGraph, TextToImport, PastedNodes);

		//Average position of nodes so we can move them while still maintaining relative distances to each other
		FVector2D AvgNodePosition(0.0f, 0.0f);

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			AvgNodePosition.X += Node->NodePosX;
			AvgNodePosition.Y += Node->NodePosY;
		}

		float InvNumNodes = 1.0f / float(PastedNodes.Num());
		AvgNodePosition.X *= InvNumNodes;
		AvgNodePosition.Y *= InvNumNodes;

		for (TSet<UEdGraphNode*>::TIterator It(PastedNodes); It; ++It)
		{
			UEdGraphNode* Node = *It;
			CurrentGraphEditor->SetNodeSelection(Node, true);

			Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + Location.X;
			Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + Location.Y;

			Node->SnapToGrid(16);

			// Give new node a different Guid from the old one
			Node->CreateNewGuid();
		}
	}

	// Update UI
	CurrentGraphEditor->NotifyGraphChanged();

	UObject* GraphOwner = EdGraph->GetOuter();
	if (GraphOwner)
	{
		GraphOwner->PostEditChange();
		GraphOwner->MarkPackageDirty();
	}
}

bool FAssetEditor_KRGDialogueGraph::CanPasteNodes()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (!CurrentGraphEditor.IsValid())
	{
		return false;
	}

	FString ClipboardContent;
	FPlatformApplicationMisc::ClipboardPaste(ClipboardContent);

	return FEdGraphUtilities::CanImportNodesFromText(CurrentGraphEditor->GetCurrentGraph(), ClipboardContent);
}

void FAssetEditor_KRGDialogueGraph::DuplicateNodes()
{
	CopySelectedNodes();
	PasteNodes();
}

bool FAssetEditor_KRGDialogueGraph::CanDuplicateNodes()
{
	return CanCopyNodes();
}

void FAssetEditor_KRGDialogueGraph::GraphSettings()
{
	//ATSDetailWidget->SetObject(EditingGraph);
}

bool FAssetEditor_KRGDialogueGraph::CanGraphSettings() const
{
	return true;
}

void FAssetEditor_KRGDialogueGraph::DockSettings()
{
	GetTabManager()->TryInvokeTab(FATSGraphAssetEditorTabs::ATSPropertyID);
}

bool FAssetEditor_KRGDialogueGraph::CanDockSettings() const
{
	return true;
}

void FAssetEditor_KRGDialogueGraph::OnRenameNode()
{
	TSharedPtr<SGraphEditor> CurrentGraphEditor = GetCurrGraphEditor();
	if (CurrentGraphEditor.IsValid())
	{
		const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
		for (FGraphPanelSelectionSet::TConstIterator NodeIt(SelectedNodes); NodeIt; ++NodeIt)
		{
			UEdGraphNode* SelectedNode = Cast<UEdGraphNode>(*NodeIt);
			if (SelectedNode != NULL && SelectedNode->bCanRenameNode)
			{
				CurrentGraphEditor->IsNodeTitleVisible(SelectedNode, true);
				break;
			}
		}
	}
}

bool FAssetEditor_KRGDialogueGraph::CanRenameNodes() const
{
	UEdKRGDialogueGraph* EdGraph = Cast<UEdKRGDialogueGraph>(EditingGraph->EdGraph);
	check(EdGraph != nullptr);

	UKRGDialogueGraph* Graph = EdGraph->GetGraph();
	check(Graph != nullptr)

	return Graph->bCanRenameNode && GetSelectedNodes().Num() == 1;
}

void FAssetEditor_KRGDialogueGraph::OnSelectedNodesChanged(const TSet<UObject*>& NewSelection)
{
	TArray<UObject*> Selection;

	for (UObject* SelectionEntry : NewSelection)
	{
		Selection.Add(SelectionEntry);
	}

	if(Selection.Num() > 0)
	{
		for(UObject* Select : Selection)
		{
			if(UEdKRGDialogueElement* Base = Cast<UEdKRGDialogueElement>(Select))
			{
				//ATSDetailWidget->SetGraphNode(Base);
				break;
			}
		}
	}
	else
	{
				
	}
}

void FAssetEditor_KRGDialogueGraph::OnNodeDoubleClicked(UEdGraphNode* Node)
{
}

void FAssetEditor_KRGDialogueGraph::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	if (EditingGraph == nullptr)
		return;

	EditingGraph->EdGraph->GetSchema()->ForceVisualizationCacheClear();
}

void FAssetEditor_KRGDialogueGraph::OnPackageSaved(const FString& PackageFileName, UObject* Outer)
{
	RebuildGraph();
}