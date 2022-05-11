// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTextActor.generated.h"

UCLASS()
class ASADAL_API ADamageTextActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageTextActor();
	
public:
	void SetText(const FString& Text, const FColor& Color);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UTextRenderComponent*		TextRenderComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector			Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float			LimitTime = 2.f;
};
