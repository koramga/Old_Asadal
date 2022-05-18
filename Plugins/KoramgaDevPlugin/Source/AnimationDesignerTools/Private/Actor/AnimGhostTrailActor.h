// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/Actor.h"
#include "AnimGhostTrailActor.generated.h"

UCLASS()
class ANIMATIONDESIGNERTOOLS_API AAnimGhostTrailActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAnimGhostTrailActor();

	void SetGhostSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent, float LifeTime = 1.f);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
	UPoseableMeshComponent*	PoseableMeshComponent;

};
