// Fill out your copyright notice in the Description page of Project Settings.


#include "Service/KRGBTService_DetectTarget.h"
#include "AbilitySystemInterface.h"
#include "KRGBTBlackboardKeys.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GAS/KRGAbilitySystemComponent.h"
#include "DrawDebugHelpers.h"

UKRGBTService_DetectTarget::UKRGBTService_DetectTarget()
{
	Interval = 0.5f;
	NodeName = TEXT("KRGDetectTarget");

	BlackboardKeys.Add(UKRGBTBlackboardKeys::TraceRangeKey);
	BlackboardKeys.Add(UKRGBTBlackboardKeys::TraceTargetKey);
}

void UKRGBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if(false == FillVariableFromComp(OwnerComp))
	{
		return;
	}

	if(false == IsValidBlackboardKeys())
	{
		return;
	}

	if(false == KRGAbilitySystemComponent->IsActivate())
	{
		return;
	}
	
	float TraceRange = OwnerBlackboardComponent->GetValueAsFloat(UKRGBTBlackboardKeys::TraceRangeKey);
	
	TArray<FHitResult> HitResults;

	FVector OwnerCharacterLocation = OwnerCharacter->GetActorLocation();

	FCollisionQueryParams param(NAME_None, true, OwnerCharacter.Get());
	GetWorld()->SweepMultiByChannel(HitResults, OwnerCharacterLocation, OwnerCharacterLocation, FQuat::Identity,  ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(TraceRange), param);

	float Distance = FLT_MAX;
	UKRGAbilitySystemComponent* TargetKRGAbilitySystemComponent = nullptr;
	
	for(const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor = HitResult.GetActor();

		if(false == HitActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
		{
			continue;
		}

		IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(HitActor);

		UKRGAbilitySystemComponent* TargetDesiredKRGAbilitySystemComponent = Cast<UKRGAbilitySystemComponent>(AbilitySystemInterface->GetAbilitySystemComponent());

		if(false == IsValid(TargetDesiredKRGAbilitySystemComponent))
		{
			continue;
		}

		if(false == TargetDesiredKRGAbilitySystemComponent->IsActivate())
		{
			continue;
		}

		FVector CharacterLocation = HitActor->GetActorLocation();

		float CurrentDistance = FVector::Distance(OwnerCharacterLocation, CharacterLocation);

		if(Distance > CurrentDistance)
		{
			TargetKRGAbilitySystemComponent = TargetDesiredKRGAbilitySystemComponent;
			Distance = CurrentDistance;
		}
	}

#ifdef ENABLE_DRAW_DEBUG

	//FColor DrawColor = TargetKRGAbilitySystemComponent ? FColor::Red : FColor::Green;
	//DrawDebugSphere(GetWorld(), OwnerCharacterLocation, TraceRange, 20, DrawColor, false, Interval);
	
#endif

	OwnerBlackboardComponent->SetValueAsObject(UKRGBTBlackboardKeys::TraceTargetKey, TargetKRGAbilitySystemComponent);
}
