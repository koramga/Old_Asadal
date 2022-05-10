// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseHUD.h"
#include "Asadal/Widget/HUD/BaseHUDWidget.h"

void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(BaseHUDWidgetClass))
	{
		BaseHUDWidget = CreateWidget<UBaseHUDWidget>(GetWorld(), BaseHUDWidgetClass);
		
		if (BaseHUDWidget)
			BaseHUDWidget->AddToViewport();
	}	
}