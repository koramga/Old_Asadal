// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotify/AnimNotify_GhostTrail.h"

#include "Actor/AnimGhostTrailActor.h"

UAnimNotify_GhostTrail::UAnimNotify_GhostTrail()
{
}

void UAnimNotify_GhostTrail::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	AActor* OwnerActor = MeshComp->GetOwner();

	FActorSpawnParameters ActorSpawnParameters;

	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParameters.Owner = OwnerActor;
	
	AAnimGhostTrailActor* AnimGhostTrailActor = MeshComp->GetWorld()->SpawnActor<AAnimGhostTrailActor>(AAnimGhostTrailActor::StaticClass(), MeshComp->GetComponentTransform(), ActorSpawnParameters);

	AnimGhostTrailActor->SetGhostSkeletalMeshComponent(MeshComp, LifeTime);

	for(const FGhostTrailMaterial& GhostTrailMaterial : GhostTrailMaterials)
	{
		AnimGhostTrailActor->SetGhostSkeletalMeshMaterial(GhostTrailMaterial.ElementIndex, GhostTrailMaterial.Material);
	}

	for(const FKRGMaterialInstanceVariable& MaterialInstanceVariable : MaterialInstanceVariables)
	{
		AnimGhostTrailActor->SetMaterialInstanceVariable(MaterialInstanceVariable);
	}
}

FString UAnimNotify_GhostTrail::GetNotifyName_Implementation() const
{
	return TEXT("GhostTrail");
}