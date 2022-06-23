#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

class FKRGDialogueElementFactory : public FGraphPanelNodeFactory
{
public:
  virtual TSharedPtr<SGraphNode> CreateNode(UEdGraphNode* Node) const override;
	
};
