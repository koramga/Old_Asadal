// Fill out your copyright notice in the Description page of Project Settings.


#include "TextActor.h"

#include "Components/TextRenderComponent.h"


// Sets default values
ATextActor::ATextActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRenderComponent"));

	SetRootComponent(TextRenderComponent);
}

void ATextActor::SetText(const FString& Text, const FColor& Color)
{
	if(IsValid(TextRenderComponent))
	{
		TextRenderComponent->SetText(FText::FromString(Text));
		TextRenderComponent->SetTextRenderColor(Color);
	}
}

// Called when the game starts or when spawned
void ATextActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LimitTime);	
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + Velocity * DeltaTime);
}

