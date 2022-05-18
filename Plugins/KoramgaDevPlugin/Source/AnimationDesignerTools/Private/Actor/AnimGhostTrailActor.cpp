// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimGhostTrailActor.h"


// Sets default values
AAnimGhostTrailActor::AAnimGhostTrailActor()
{
	//https://mingyu0403.tistory.com/247
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PoseableMeshComponent = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMeshComponent"));

	SetRootComponent(PoseableMeshComponent);
}

void AAnimGhostTrailActor::SetGhostSkeletalMeshComponent(USkeletalMeshComponent* SkeletalMeshComponent, float LifeTime)
{
	if(IsValid(PoseableMeshComponent))
	{
		PoseableMeshComponent->SetSkeletalMesh(SkeletalMeshComponent->SkeletalMesh);
		PoseableMeshComponent->CopyPoseFromSkeletalComponent(SkeletalMeshComponent);

		SetLifeSpan(LifeTime);
	}
}

// Called when the game starts or when spawned
void AAnimGhostTrailActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAnimGhostTrailActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}