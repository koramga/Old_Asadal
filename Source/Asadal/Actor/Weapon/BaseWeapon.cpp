// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "Asadal/Character/BaseCharacter.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseWeapon::SetActivateCollision(bool bIsActivate)
{
	if(bIsActivate)
	{
		for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : CollisionComponents)
		{
			PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			TArray<AActor*> OverlappingActors;
			
			PrimitiveComponent->GetOverlappingActors(OverlappingActors, ABaseCharacter::StaticClass());

			for(AActor* OverlappingActor : OverlappingActors)
			{
				//HitResult 넘겨주자
				FOverlapEventData OverlapEventData;

				OverlapEventData.OtherActor = OverlappingActor;
				
				OnBaseWeaponOverlapBeginEvent.Broadcast(OverlapEventData);
			}
		}
	}
	else
	{
		for(TSoftObjectPtr<UPrimitiveComponent> PrimitiveComponent : CollisionComponents)
		{
			PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> PrimitiveComponents;
	
	GetComponents(UPrimitiveComponent::StaticClass(), PrimitiveComponents);

	for(int PrimitiveComponentIndex = 0; PrimitiveComponentIndex < PrimitiveComponents.Num(); ++PrimitiveComponentIndex)
	{
		if(true == CollisionComponentNames.Contains(PrimitiveComponents[PrimitiveComponentIndex]->GetName()))
		{
			UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(PrimitiveComponents[PrimitiveComponentIndex]);
			
			PrimitiveComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseWeapon::__OnComponentOverlapNative);
			
			CollisionComponents.Add(PrimitiveComponent);
		}
	}
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::__OnComponentOverlapNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	FOverlapEventData OverlapEventData;

	OverlapEventData.OtherActor = OtherActor;
	
	OnBaseWeaponOverlapBeginEvent.Broadcast(OverlapEventData);
}