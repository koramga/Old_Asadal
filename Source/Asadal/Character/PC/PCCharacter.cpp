// Fill out your copyright notice in the Description page of Project Settings.


#include "PCCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Asadal/Asadal.h"
#include "Asadal/Actor/Object/Equipment/Weapon/BaseWeapon.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "KRGGASItem/Public/Fragment/KRGGASFragment_EquipableItem.h"


// Sets default values
APCCharacter::APCCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	//Arm을 Root에 붙여준다.
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera를 Arm에 붙여준다.
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APCCharacter::InputMoveForward(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveForward <%.2f>"), Value);
	
	if (IsValid(Controller))
	{
		//if (Cast<ACPlayerController>(Controller)->bOnClick) return;
		// find out which way is forward
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APCCharacter::InputMoveRight(float Value)
{
	//UE_LOG(LogTemp, Display, TEXT("MoveRight <%.2f>"), Value);
	
	if (IsValid(Controller))
	{
		//	if (Cast<ACPlayerController>(Controller)->bOnClick) return;
		// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, QUARTER_VIEW_ANGLE, 0.f);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

UTexture2D* APCCharacter::GetPCSkillIconByIndex(int32 Index)
{
	const FGameplayAbilityActionGroup* AbilityActionGroup = GASComponent->GetActivateAbilityActionGroup();
	
	if(nullptr != AbilityActionGroup
		&& AbilityActionGroup->AttackAbilityFragmentHandles.Num() > Index)
	{
		return AbilityActionGroup->AttackAbilityFragmentHandles[Index].KRGGASAbilityInfo->IconTexture;
	}

	return nullptr;
}

bool APCCharacter::TryActivateSkillByIndex(int32 Index)
{
	return GASComponent->TryAttackAbilityFromActionGroup(Index);
}

void APCCharacter::TryActivateEquipment(const FGameplayTag& GameplayTag, bool bIsActivate)
{
	Super::TryActivateEquipment(GameplayTag, bIsActivate);
	
	if(ActivateWeaponDefinition.IsValid())
	{
	    UKRGGASFragment_EquipableItem* WeaponFragmentEquippableItem = ActivateWeaponDefinition->FindFragment<UKRGGASFragment_EquipableItem>();

		const TArray<TSoftObjectPtr<AActor>>& SpawnEquipmentActors = WeaponFragmentEquippableItem->GetSpawnEquipmentActors();

		for(TSoftObjectPtr<AActor> SpawnEquipmentActor : SpawnEquipmentActors)
		{
			ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(SpawnEquipmentActor.Get());

			if(IsValid(BaseWeapon))
			{
				BaseWeapon->SetActivateCollision(bIsActivate);
			}
		}
	}

}

// Called when the game starts or when spawned
void APCCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//bool APCCharacter::HasSkill(uint32_t Index)
//{
//	FString GameplayTagName = FString::Printf(TEXT("PC.Ability.%d"), Index);
//	
//	FGameplayTag GameplayTag = FGameplayTag::RequestGameplayTag(FName(GameplayTagName, false));
//
//	FGameplayTagContainer GameplayTagContainer;
//	GameplayTagContainer.AddTag(GameplayTag);
//
//	TArray<FGameplayAbilitySpec*> GameplayAbilitySpecs;
//	
//	GASComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(GameplayTagContainer, GameplayAbilitySpecs);
//
//	//for(FGameplayAbilitySpec* AbilitySpec : GameplayAbilitySpecs)
//	//{
//	//	AbilitySpec->Ability
//	//}
//
//	if(GameplayAbilitySpecs.Num() > 0)
//	{
//		return true;
//	}
//	
//	//if(GameplayTag.IsValid())
//	//{
//	//	return GASComponent->HasMatchingGameplayTag(GameplayTag);
//	//}
//
//	return false;
//}
