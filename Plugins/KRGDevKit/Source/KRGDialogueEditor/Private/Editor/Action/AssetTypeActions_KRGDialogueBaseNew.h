﻿#pragma once
#include "AssetTypeActions_Base.h"

class FAssetTypeActions_KRGDialogueBaseNew : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_KRGDialogueBaseNew(EAssetTypeCategories::Type InAssetCategory);

	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};
