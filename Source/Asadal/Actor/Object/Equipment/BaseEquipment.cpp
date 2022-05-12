// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEquipment.h"

#include "Asadal/Character/BaseCharacter.h"


// Sets default values
ABaseEquipment::ABaseEquipment()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseEquipment::SetEquip(bool bIsEquip)
{
	AActor* OwnerActor = GetOwner();

	if(false == IsValid(OwnerActor))
	{
		UChildActorComponent* ChildActorComponent = GetParentComponent();

		if(IsValid(ChildActorComponent))
		{
			OwnerActor = ChildActorComponent->GetOwner();
		}
	}
	
	ABaseCharacter* BaseCharacter = Cast<ABaseCharacter>(OwnerActor);

	if(IsValid(BaseCharacter))
	{
		if(bIsEquip)
		{
			BaseCharacter->AddLooseGameplayTag(WeaponGameplayTag);
		}
		else
		{
			BaseCharacter->RemoveLooseGameplayTag(WeaponGameplayTag);			
		}
	}
}

void ABaseEquipment::SetActivateCollision(bool bIsActivate)
{
	AlreadyOverlapActors.Empty();
	
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
				OnEquipmentOverlapBroadcast(OverlappingActor);
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
void ABaseEquipment::BeginPlay()
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
			PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &ABaseEquipment::__OnComponentOverlapNative);
			
			CollisionComponents.Add(PrimitiveComponent);
		}
	}	
}

// Called every frame
void ABaseEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseEquipment::OnEquipmentOverlapBroadcast(AActor* OtherActor)
{
	AActor* EquipmentOwner = GetOwner();

	if(false ==  IsValid(EquipmentOwner))
	{
		UChildActorComponent* ChildActorComponent = GetParentComponent();

		if(IsValid(ChildActorComponent))
		{
			EquipmentOwner = ChildActorComponent->GetOwner();
		}
	}
	
	if(EquipmentOwner != OtherActor)
	{
		if(false == AlreadyOverlapActors.Contains(OtherActor))
		{
			AlreadyOverlapActors.Add(OtherActor);
		
			FEquipmentOverlapEventData OverlapEventData;

			OverlapEventData.Caller = this;
			OverlapEventData.OtherActor = OtherActor;
	
			OnEquipmentOverlapEvent.Broadcast(OverlapEventData);		
		}		
	}	
}

void ABaseEquipment::__OnComponentOverlapNative(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnEquipmentOverlapBroadcast(OtherActor);
}