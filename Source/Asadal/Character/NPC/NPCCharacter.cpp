// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"

#include "Asadal/Widget/Screen/ScreenNPCStatusWidget.h"
#include "Components/WidgetComponent.h"


// Sets default values
ANPCCharacter::ANPCCharacter()
{

}

//UKRGAIDefinition* ANPCCharacter::GetKRGAIDefinition() const
//{
//	return KRGAIDefinition;
//}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> ActorComponents;
	
	GetComponents(UWidgetComponent::StaticClass(), ActorComponents);

	for(UActorComponent* ActorComponent : ActorComponents)
	{
		UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(ActorComponent);

		if(IsValid(WidgetComponent))
		{
			if(WidgetComponent->GetWidget()->IsA(UScreenNPCStatusWidget::StaticClass()))
			{
				ScreenNPCStatusWidget = Cast<UScreenNPCStatusWidget>(WidgetComponent->GetWidget());
			}
		}
	}

	UpdateStatusWidgetOnHealth();
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANPCCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	Super::OnHealthChanged(Data);
	
	UpdateStatusWidgetOnHealth();
}

void ANPCCharacter::UpdateDeath(bool bIsDeath)
{
	Super::UpdateDeath(bIsDeath);

	if(true == bIsDeath)
	{
		ScreenNPCStatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		ScreenNPCStatusWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ANPCCharacter::UpdateStatusWidgetOnHealth()
{
	if(ScreenNPCStatusWidget.IsValid())
	{
		float Health, MaxHealth;
		GetHealthValues(Health, MaxHealth);

		ScreenNPCStatusWidget->SetHealthPercent(Health / MaxHealth);		
	}
}
