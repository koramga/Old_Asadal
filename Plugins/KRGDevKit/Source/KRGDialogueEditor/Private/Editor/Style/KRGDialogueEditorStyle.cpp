﻿#include "KRGDialogueEditorStyle.h"

#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<FSlateStyleSet> FKRGDialogueEditorStyle::StyleSet = nullptr;

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( StyleSet->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define TTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".ttf") ), __VA_ARGS__ )
#define OTF_FONT( RelativePath, ... ) FSlateFontInfo( StyleSet->RootToContentDir( RelativePath, TEXT(".otf") ), __VA_ARGS__ )

void FKRGDialogueEditorStyle::Initialize()
{
	const FVector2D Icon20x20(20.f, 20.f);
	const FVector2D Icon40x40(40.f, 40.f);
	const FVector2D Icon64x64(64.f, 64.f);

	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet("ScriptGraphEditorStyle"));

	StyleSet->SetContentRoot(FPaths::ProjectPluginsDir() / TEXT("ScriptGraph/Resources"));

	StyleSet->Set("ScriptGraphEditor.AutoArrange", new IMAGE_BRUSH("AutoArrangeIcon", Icon40x40));
	StyleSet->Set("ScriptGraphEditor.AutoArrange.Small", new IMAGE_BRUSH("AutoArrangeIcon", Icon20x20));

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FKRGDialogueEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}

const FName& FKRGDialogueEditorStyle::GetStyleSetName()
{
	return StyleSet->GetStyleSetName();
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef TTF_FONT
#undef OTF_FONT