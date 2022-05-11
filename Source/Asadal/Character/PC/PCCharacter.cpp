// Fill out your copyright notice in the Description page of Project Settings.


#include "PCCharacter.h"
#include "Asadal/Asadal.h"
#include "Asadal/Actor/eQUIPMENT/Weapon/BaseWeapon.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


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

FGameplayAbilitySpec* APCCharacter::GetPCSkillAbilitySpecByIndex(int32 Index)
{
	if(PlayerSkillSet.Num() > Index)
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = PlayerSkillSet[Index];

		if(AbilitySpecHandle.IsValid())
		{
			return GASComponent->FindAbilitySpecFromHandle(AbilitySpecHandle);
		}
	}

	return nullptr;
}

bool APCCharacter::TryActivateSkillByIndex(int32 Index)
{
	if(PlayerSkillSet.Num() > Index)
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = PlayerSkillSet[Index];

		if(AbilitySpecHandle.IsValid())
		{
			if(GASComponent->TryActivateAbility(AbilitySpecHandle))
			{
				UE_LOG(LogTemp, Display, TEXT("TryActivateAbility Success"));
				return true;
			}
			else
			{
				UE_LOG(LogTemp, Display, TEXT("TryActivateAbility Failed"));
			}
		}
	}

	return false;
}

void APCCharacter::SetActivateEquipment(FGameplayTag GameplayTag, bool bIsActivate)
{
	Super::SetActivateEquipment(GameplayTag, bIsActivate);

	FGameplayTag WeaponGameplayTag = FGameplayTag::RequestGameplayTag("Object.Weapon");

	if(GameplayTag.MatchesTag(WeaponGameplayTag))
	{
		//Weapon이구나!
		for(TSoftObjectPtr<UChildActorComponent> ChildActorComponent : BaseWeapons)
		{
			if(ChildActorComponent->GetChildActor()->IsA(ABaseWeapon::StaticClass()))
			{
				ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(ChildActorComponent->GetChildActor());

				if(IsValid(BaseWeapon))
				{
					BaseWeapon->SetActivateCollision(bIsActivate);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void APCCharacter::BeginPlay()
{
	Super::BeginPlay();

	for(int i = 0; i < PlayerSkillAbilityClasses.Num(); ++i)
	{
		if(i >= MAX_PC_SKILL_COUNT)
		{
			break;
		}

		PlayerSkillSet.Add(InitializeAbility(PlayerSkillAbilityClasses[i], 0));
	}
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
