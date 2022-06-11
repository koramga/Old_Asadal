// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/KRGGASBTComponent.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/KRGAbilitySystemComponent.h"
#include "Definition/KRGGASDefinition.h"
#include "Definition/Fragment/KRGGASFragment_BTBase.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UKRGGASBTComponent::UKRGGASBTComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UKRGGASBTComponent::SetKRGAbilitySystemComponent(UKRGAbilitySystemComponent* AbilitySystemComponent)
{
	KRGAbilitySystemComponent = AbilitySystemComponent;
}

void UKRGGASBTComponent::SetBlackboardData(AAIController* AIController)
{
	UKRGGASDefinition* KRGGASAIDefinition = Cast<UKRGGASDefinition>(AIDefinition);

	if(IsValid(KRGGASAIDefinition))
	{
		if(IsValid(AIController))
		{
			UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent();

			if(IsValid(BlackboardComponent))
			{
				//여기서 부터 시작한다.
				TArray<UKRGGASFragment_BTBase*> BTBases = KRGGASAIDefinition->FindFragments<UKRGGASFragment_BTBase>();

				for(UKRGGASFragment_BTBase* BTBase : BTBases)
				{
					BTBase->SetupBlackboard(BlackboardComponent);
				}
			}
		}		
	}
}


// Called when the game starts
void UKRGGASBTComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

// Called every frame
void UKRGGASBTComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

