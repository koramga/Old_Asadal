#include "KRGDialogueGraphDragConnection.h"
#include "SGraphPanel.h"
#include "Node/Node/EdKRGDialogueNode.h"


TSharedRef<FKRGDialogueGraphDragConnection> FKRGDialogueGraphDragConnection::New(const TSharedRef<SGraphPanel>& InGraphPanel,
                                                                                 const FDraggedPinTable& InStartingPins)
{
	TSharedRef<FKRGDialogueGraphDragConnection> Operation = MakeShareable(new FKRGDialogueGraphDragConnection(InGraphPanel, InStartingPins));
	Operation->Construct();

	return Operation;
}

void FKRGDialogueGraphDragConnection::OnDrop(bool bDropWasHandled, const FPointerEvent& MouseEvent)
{
	GraphPanel->OnStopMakingConnection();
	
	Super::OnDrop(bDropWasHandled, MouseEvent);
}

void FKRGDialogueGraphDragConnection::HoverTargetChanged()
{
	TArray<FPinConnectionResponse> UniqueMessages;

	if(UEdGraphPin* TargetPinObj = GetHoveredPin())
	{
		TArray<UEdGraphPin*> ValidSourcePin;
		ValidateGraphPinList(ValidSourcePin);

		//Check the schema for connection responses
		for(UEdGraphPin* StartingPinObj : ValidSourcePin)
		{
			//The Graph object in which the pins reside
			UEdGraph* GraphObj = StartingPinObj->GetOwningNode()->GetGraph();

			//Determine what the schema thinks about the wiring action
			const FPinConnectionResponse Response = GraphObj->GetSchema()->CanCreateConnection(StartingPinObj, TargetPinObj);

			if(Response.Response == ECanCreateConnectionResponse::CONNECT_RESPONSE_DISALLOW)
			{
				TSharedPtr<SGraphNode> NodeWidget = TargetPinObj->GetOwningNode()->DEPRECATED_NodeWidget.Pin();

				if(NodeWidget.IsValid())
				{
					NodeWidget->NotifyDisallowedPinConnection(StartingPinObj, TargetPinObj);
				}
			}
			
			UniqueMessages.AddUnique(Response);
		}
	}
	else if(UEdKRGDialogueNode* TargetNodeObj = Cast<UEdKRGDialogueNode>(GetHoveredNode()))
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		//Check the schema for connection responses
		for(UEdGraphPin* StartingPinObj : ValidSourcePins)
		{
			FPinConnectionResponse Response;
			FText ResponseText;

			const UEdGraphSchema* Schema = StartingPinObj->GetSchema();
			UEdGraphPin* TargetPin = TargetNodeObj->GetInputPin();

			if(Schema && TargetPin)
			{
				Response = Schema->CanCreateConnection(StartingPinObj, TargetPin);
				if(Response.Response == CONNECT_RESPONSE_DISALLOW)
				{
					TSharedPtr<SGraphNode> NodeWidget = TargetPin->GetOwningNode()->DEPRECATED_NodeWidget.Pin();

					if(NodeWidget.IsValid())
					{
						NodeWidget->NotifyDisallowedPinConnection(StartingPinObj, TargetPinObj);
					}
				}
			}
			else
			{
				Response = FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Not a valid EdGraphNode_ATSBaseNode"));
			}

			UniqueMessages.AddUnique(Response);
		}
	}
	else if(UEdGraph* CurrentHoveredGraph = GetHoveredGraph())
	{
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		for(UEdGraphPin* StartingPinObj : ValidSourcePins)
		{
			//Let the scema describe the connection we might make
			FPinConnectionResponse Response = CurrentHoveredGraph->GetSchema()->CanCreateNewNodes(StartingPinObj);
			if(!Response.Message.IsEmpty())
			{
				UniqueMessages.AddUnique(Response);
			}
		}
	}

	//Let the user know the status of dropping now
	if(UniqueMessages.Num() == 0)
	{
		//Display the place a new node icon, we're not over a valid pin and have no message from the schema.
		SetSimpleFeedbackMessage(
			FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.NewNode")),
			FLinearColor::White,
			FText::FromString(TEXT("PlaceNewNode")));
	}
	else
	{
		//Take the unique responses and create visual feedback for it
		TSharedRef<SVerticalBox> FeedbackBox = SNew(SVerticalBox);
		for(auto ResponseIt = UniqueMessages.CreateConstIterator(); ResponseIt; ++ResponseIt)
		{
			//Determine the icon
			const FSlateBrush* StatusSymbol = NULL;

			switch (ResponseIt->Response)
			{
			case CONNECT_RESPONSE_MAKE :
			case CONNECT_RESPONSE_BREAK_OTHERS_A :
			case CONNECT_RESPONSE_BREAK_OTHERS_B :
			case CONNECT_RESPONSE_BREAK_OTHERS_AB :
				StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.OK"));
				break;

			case CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE :
				StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.ViaCast"));
				break;

			case CONNECT_RESPONSE_DISALLOW :
				StatusSymbol = FEditorStyle::GetBrush(TEXT("Graph.ConnectorFeedback.Error"));
				break;
			}

			//Add a new message row
			FeedbackBox->AddSlot()
				.AutoHeight()
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.Padding(3.f)
					.VAlign(VAlign_Center)
					[
						SNew(SImage).Image(StatusSymbol)
					]
					+ SHorizontalBox::Slot()
					.AutoWidth()
					.VAlign(VAlign_Center)
					[
						SNew(STextBlock).Text(ResponseIt->Message)
					]
				];
		}

		SetFeedbackMessage(FeedbackBox);
	}
}

FReply FKRGDialogueGraphDragConnection::DroppedOnPin(FVector2D ScreenPosition, FVector2D GraphPosition)
{
	TArray<UEdGraphPin*> ValidSourcePins;
	ValidateGraphPinList(ValidSourcePins);

	const FScopedTransaction Transation(FText::FromString(TEXT("Create Pin Link")));

	UEdGraphPin* PinB = GetHoveredPin();
	bool bError = false;
	TSet<UEdGraphNode*> NodeList;

	for(UEdGraphPin* PinA : ValidSourcePins)
	{
		if((PinA != NULL) && (PinB != NULL))
		{
			UEdGraph* MyGraphObj = PinA->GetOwningNode()->GetGraph();

			if(MyGraphObj->GetSchema()->TryCreateConnection(PinA, PinB))
			{
				if(!PinA->IsPendingKill())
				{
					NodeList.Add(PinA->GetOwningNode());
				}
				if(!PinB->IsPendingKill())
				{
					NodeList.Add(PinB->GetOwningNode());
				}
			}
		}
		else
		{
			bError = true;
		}
	}

	//Send all nodes that received a new pin connection a notification
	for(auto It = NodeList.CreateConstIterator(); It; ++It)
	{
		UEdGraphNode* Node = (*It);
		Node->NodeConnectionListChanged();
	}

	if(bError)
	{
		return FReply::Unhandled();
	}

	return FReply::Handled();
}

FReply FKRGDialogueGraphDragConnection::DroppedOnNode(FVector2D ScreenPosition, FVector2D GraphPosition)
{
	bool bHandledPinDropOnNode = false;
	UEdGraphNode* NodeOver = GetHoveredNode();

	if(NodeOver)
	{
		//Gather any source drag pins
		TArray<UEdGraphPin*> ValidSourcePins;
		ValidateGraphPinList(ValidSourcePins);

		if(ValidSourcePins.Num())
		{
			for(UEdGraphPin* SourcePin : ValidSourcePins)
			{
				//check for pin drop support
				FText ResponseText;
				if(SourcePin->GetOwningNode() != NodeOver && SourcePin->GetSchema()->SupportsDropPinOnNode(NodeOver, SourcePin->PinType, SourcePin->Direction, ResponseText))
				{
					bHandledPinDropOnNode = true;

					//Find which pin name to use and drop the pin on the node
					const FName PinName = SourcePin->PinFriendlyName.IsEmpty() ? SourcePin->PinName : *SourcePin->PinFriendlyName.ToString();

					const FScopedTransaction Transaction((SourcePin->Direction == EGPD_Output ? FText::FromString(TEXT("Add In Parameter")) : FText::FromString(TEXT("Add Out Paramter"))));

					UEdGraphPin* EdGraphPin = NodeOver->GetSchema()->DropPinOnNode(GetHoveredNode(), PinName, SourcePin->PinType, SourcePin->Direction);

					//This can invalidate the source pin due to node reconstruction, abort in that case
					if(SourcePin->GetOwningNodeUnchecked() && EdGraphPin)
					{
						SourcePin->Modify();
						EdGraphPin->Modify();
						SourcePin->GetSchema()->TryCreateConnection(SourcePin, EdGraphPin);
					}
				}

				//If we have not handled the pin drop on node and there is an error message, do not let other actions occur.
				if(!bHandledPinDropOnNode && !ResponseText.IsEmpty())
				{
					bHandledPinDropOnNode = true;
				}
			}
		}
	}

	return bHandledPinDropOnNode ? FReply::Handled() : FReply::Unhandled();
}

FReply FKRGDialogueGraphDragConnection::DroppedOnPanel(const TSharedRef<SWidget>& Panel, FVector2D ScreenPosition,
	FVector2D GraphPosition, UEdGraph& Graph)
{
	TArray<UEdGraphPin*> PinObjects;
	ValidateGraphPinList(PinObjects);

	//Create a context menu
	TSharedPtr<SWidget> WidgetToFocus = GraphPanel->SummonContextMenu(ScreenPosition, GraphPosition, NULL, NULL, PinObjects);

	//Give the context menu focus
	return (WidgetToFocus.IsValid()) ? FReply::Handled().SetUserFocus(WidgetToFocus.ToSharedRef(), EFocusCause::SetDirectly) : FReply::Handled();
}

void FKRGDialogueGraphDragConnection::OnDragged(const FDragDropEvent& DragDropEvent)
{
	FVector2D TargetPosition = DragDropEvent.GetScreenSpacePosition();

	//Reposition the info window wrt to the drag
	CursorDecoratorWindow->MoveWindowTo(DragDropEvent.GetScreenSpacePosition() + DecoratorAdjust);
	//Request the active panel to scroll if requred
	GraphPanel->RequestDeferredPan(TargetPosition);
}

void FKRGDialogueGraphDragConnection::ValidateGraphPinList(TArray<UEdGraphPin*>& OutValidPins)
{
	OutValidPins.Empty(DraggingPins.Num());
	for(const FGraphPinHandle& PinHandle : DraggingPins)
	{
		if(UEdGraphPin* GraphPin = PinHandle.GetPinObj(*GraphPanel))
		{
			OutValidPins.Add(GraphPin);
		}
	}
}

FKRGDialogueGraphDragConnection::FKRGDialogueGraphDragConnection(const TSharedRef<SGraphPanel>& InGraphPanel,
                                                 const FDraggedPinTable& InDraggedPins)
	: GraphPanel(InGraphPanel)
	, DraggingPins(InDraggedPins)
	, DecoratorAdjust(FSlateApplication::Get().GetCursorSize())
{
	if(DraggingPins.Num() > 0)
	{
		const UEdGraphPin* PinObj = FDraggedPinTable::TConstIterator(InDraggedPins)->GetPinObj(*InGraphPanel);
		if(PinObj && PinObj->Direction == EGPD_Input)
		{
			DecoratorAdjust *= FVector2D(-1.f, 1.f);
		}
	}

	for(const FGraphPinHandle& DraggedPin : InDraggedPins)
	{
		InGraphPanel->OnBeginMakingConnection(DraggedPin);
	}
}
