// Fill out your copyright notice in the Description page of Project Settings.


#include "SEdKRGDialogueNode_Branch.h"

#include "SlateOptMacros.h"
#include "Element/Node/KRGDialogueNode_Branch.h"
#include "Node/Node/EdKRGDialogueNode_Branch.h"

void SEdKRGDialogueNode_Branch::Construct(const FArguments& InArgs)
{
	GraphNode = InArgs._EdGraphNode;
	InitializeNode();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SEdKRGDialogueNode_Branch::UpdateGraphNode()
{
	SEdKRGDialogueNode::UpdateGraphNode();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdKRGDialogueNode_Branch::SetDefaultTitleAreaWidget(TSharedRef<SOverlay> DefaultTitleAreaWidget)
{
	DefaultTitleAreaWidget->ClearChildren();

	TSharedPtr<SVerticalBox> VerticalBox;
	
	SAssignNew(VerticalBox, SVerticalBox);

	UEdKRGDialogueNode_Branch* EdCraftNode = Cast<UEdKRGDialogueNode_Branch>(GraphNode);

	if(IsValid(EdCraftNode))
	{
		UKRGDialogueNode* BaseNode = EdCraftNode->GetNode();
		
		if(IsValid(BaseNode))
		{
			UKRGDialogueNode_Branch* ATSCraftNode = Cast<UKRGDialogueNode_Branch>(BaseNode);
			TArray<FString> TitleStrings;
			
			//if(IsValid(ATSCraftNode))
			//{
			//	TitleStrings = ATSCraftNode->GetTaskNames();
			//}
			
			for(const FString& TitleString : TitleStrings)
			{
				VerticalBox->AddSlot()
				[
					SNew(STextBlock)
					.Text(FText::FromString(TitleString))
				];
			}
		}
	}
	
	
	
	DefaultTitleAreaWidget->AddSlot()
	[
		SNew(SImage)
		.Image( FAppStyle::GetBrush("Graph.Node.TitleGloss") )
		.ColorAndOpacity( this, &SGraphNode::GetNodeTitleIconColor )
	];

	DefaultTitleAreaWidget->AddSlot()
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Center)
	[
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.HAlign(HAlign_Fill)
		[
			SNew(SBorder)
			.BorderImage( FAppStyle::GetBrush("Graph.Node.ColorSpill") )
			.Padding( FMargin(10,5,30,3) )
			.BorderBackgroundColor( this, &SGraphNode::GetNodeTitleColor )
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				VerticalBox.ToSharedRef()
			]
		]
	];
}
