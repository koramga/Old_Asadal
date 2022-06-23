#include "SEdKRGDialogueElement.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SEdKRGDialogueElement::Construct(const FArguments& InArgs)
{
	EdGraphNode = InArgs._EdGraphNode;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
