// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Definition/KRGGASDefinition.h"
#include "Definition/Fragment/KRGGASFragment_BTMove.h"
#include "KRGGASBTComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class KRGGASBT_API UKRGGASBTComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UKRGGASBTComponent();

public:
	void SetKRGAbilitySystemComponent(class UKRGAbilitySystemComponent* AbilitySystemComponent);
	void SetBlackboardData(class AAIController* AIController);

public :
	UKRGGASDefinition*	GetKRGGASDefinition() const;
	UKRGGASFragment_BTMove* GetMoveFragment() const;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Setup|Definition")
	UDataAsset*											AIDefinition;
	
	TSoftObjectPtr<class UKRGAbilitySystemComponent>	KRGAbilitySystemComponent;
};
