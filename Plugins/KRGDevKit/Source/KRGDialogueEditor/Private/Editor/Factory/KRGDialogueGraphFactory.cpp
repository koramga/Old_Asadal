// Fill out your copyright notice in the Description page of Project Settings.


#include "KRGDialogueGraphFactory.h"
#include "ClassViewerModule.h"
#include "ClassViewerFilter.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/SClassPickerDialog.h"

class FAssetClassParentFilter : public IClassViewerFilter
{
public :
	FAssetClassParentFilter()
		: DisallowedClassFlags(CLASS_None), bDisallowBlueprintBase(false)
	{}

	virtual bool IsClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const UClass* InClass, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		bool bAllowed = !InClass->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InClass) != EFilterReturn::Failed;

		if(bAllowed && bDisallowBlueprintBase)
		{
			if(FKismetEditorUtilities::CanCreateBlueprintOfClass(InClass))
			{
				return false;
			}
		}

		return bAllowed;
	}

	virtual bool IsUnloadedClassAllowed(const FClassViewerInitializationOptions& InInitOptions, const TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData, TSharedRef<FClassViewerFilterFuncs> InFilterFuncs) override
	{
		if(bDisallowBlueprintBase)
		{
			return false;
		}

		return !InUnloadedClassData->HasAnyClassFlags(DisallowedClassFlags) && InFilterFuncs->IfInChildOfClassesSet(AllowedChildrenOfClasses, InUnloadedClassData) != EFilterReturn::Failed;
	}

	void SetDisallowedClassFlags(EClassFlags Flags)
	{
		DisallowedClassFlags = Flags;
	}

	void AddAllowedChildClass(UClass* Class)
	{
		AllowedChildrenOfClasses.Add(Class);
	}
	

private:
	// All children of these classes will be included unless filtered out by another setting.
	TSet<const UClass*> AllowedChildrenOfClasses;
	
	/** Disallowed class flags. */
	EClassFlags DisallowedClassFlags;

	/** Disallow blueprint base classes. */
	bool bDisallowBlueprintBase;
};

UKRGDialogueGraphFactory::UKRGDialogueGraphFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UKRGDialogueGraph::StaticClass();
}

UKRGDialogueGraphFactory::~UKRGDialogueGraphFactory()
{
}

bool UKRGDialogueGraphFactory::ConfigureProperties()
{
	//nullptr the ATSBaseGraphClass so we can check for selection.
	BaseGraphClass = nullptr;

	//Load the classviewer module to display a class picker
	FClassViewerModule& ClassViewerModule = FModuleManager::LoadModuleChecked<FClassViewerModule>("ClassViewer");

	//Fill in options.
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;

	TSharedPtr<FAssetClassParentFilter> Filter = MakeShareable(new FAssetClassParentFilter);
	Options.ClassFilter = Filter;

	Filter->SetDisallowedClassFlags(CLASS_Abstract | CLASS_Deprecated | CLASS_NewerVersionExists | CLASS_HideDropDown);
	Filter->AddAllowedChildClass(UKRGDialogueGraph::StaticClass());

	const FText TitleText = FText::FromString(TEXT("Pick Automation Testing Graph Class"));
	UClass* ChosenClass = nullptr;
	const bool bPressedOK = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, UKRGDialogueGraph::StaticClass());

	if(bPressedOK)
	{
		BaseGraphClass = ChosenClass;
	}

	return bPressedOK;	
}

UObject* UKRGDialogueGraphFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	if(BaseGraphClass != nullptr)
	{
		return NewObject<UKRGDialogueGraph>(InParent, BaseGraphClass, InName, Flags | RF_Transactional);
	}
	
	return Super::FactoryCreateNew(InClass, InParent, InName, Flags, Context, Warn);
}
