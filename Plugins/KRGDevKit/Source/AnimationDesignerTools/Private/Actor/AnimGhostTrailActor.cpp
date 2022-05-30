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

void AAnimGhostTrailActor::SetGhostSkeletalMeshMaterial(int32 ElementIndex, UMaterial* Material)
{
	PoseableMeshComponent->SetMaterial(ElementIndex, Material);
}

void AAnimGhostTrailActor::SetMaterialInstanceVariable(const FMaterialInstanceVariable& MaterialInstanceVariable)
{
	MaterialInstanceVariables.Add(MaterialInstanceVariable);

	FMaterialInstanceVariable& NewMaterialInstanceVariable = MaterialInstanceVariables[MaterialInstanceVariables.Num() - 1];

	NewMaterialInstanceVariable.SetMaterialInstanceParameter(PoseableMeshComponent);
	NewMaterialInstanceVariable.StartUpdate();
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

	for(FMaterialInstanceVariable& MaterialInstanceVariable : MaterialInstanceVariables)
	{
		MaterialInstanceVariable.Update(PoseableMeshComponent, DeltaTime);
	}
}