// Fill out your copyright notice in the Description page of Project Settings.


#include "PCCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Asadal/Asadal.h"
#include "Asadal/Actor/Object/Equipment/Weapon/BaseWeapon.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"
#include "Asadal/Inventory/AsadalInventoryItemDefinition.h"
#include "Asadal/Inventory/Fragment/InventoryFragment_EquippableItem.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
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

void APCCharacter::TryActivateEquipment(FGameplayTag GameplayTag, bool bIsActivate)
{
	Super::TryActivateEquipment(GameplayTag, bIsActivate);

	UInventoryFragment_EquippableItem* WeaponFragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(EquipmentWepaonItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

	WeaponFragmentEquippableItem->SetActivateCollisions(bIsActivate);
}

void APCCharacter::SetEquipInventoryItem(TSoftObjectPtr<UAsadalInventoryItemDefinition> InventoryItemDefinition)
{
	UInventoryFragment_EquippableItem* FragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(InventoryItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

	if(IsValid(FragmentEquippableItem))
	{
		if(FragmentEquippableItem->HasGameplayTag(UAsadalGameplayTags::ObjectWeaponTag))
		{
			//Weapon입니다.

			if(InventoryItemDefinition != EquipmentWepaonItemDefinition)
			{
				if(EquipmentWepaonItemDefinition.IsValid())
				{
					UInventoryFragment_EquippableItem* EquipmentFragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(EquipmentWepaonItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

					EquipmentFragmentEquippableItem->SetEquip(this, false);
				}

				if(IsValid(FragmentEquippableItem))
				{
					FragmentEquippableItem->SetEquip(this, true);
					const TArray<TSoftObjectPtr<ABaseEquipment>>& Equipments = FragmentEquippableItem->GetSpawnEquipmentActors();

					for(TSoftObjectPtr<ABaseEquipment> BaseEquipment : Equipments)
					{
						BaseEquipment->OnEquipmentOverlapEvent.AddDynamic(this, &APCCharacter::__OnEquipmentOverlapEventNative);
					}
				}

				EquipmentWepaonItemDefinition = InventoryItemDefinition;
			}
		}
	}
}

void APCCharacter::TryEquipNextWeapon()
{
	if(EquipmentWeaponItemDefinitions.Num() > 0)
	{
		if(false == EquipmentWepaonItemDefinition.IsValid())
		{
			SetEquipInventoryItem(EquipmentWeaponItemDefinitions[0]);			
		}
		else
		{
			int32 Index = EquipmentWeaponItemDefinitions.Find(EquipmentWepaonItemDefinition);

			if(Index != INDEX_NONE)
			{
				Index = (Index + 1) % EquipmentWeaponItemDefinitions.Num();

				SetEquipInventoryItem(EquipmentWeaponItemDefinitions[Index]);
			}
		}
	}

	if(EquipmentWepaonItemDefinition.IsValid())
	{
		UInventoryFragment_EquippableItem* EquipmentFragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(EquipmentWepaonItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

		if(IsValid(EquipmentFragmentEquippableItem))
		{
			const TArray<FGameplayAbilitySpecHandle>* SpecOnWeapons = PlayerAnimationOnWeapons.Find(EquipmentFragmentEquippableItem->GetEquipmentGameplayTag());

			for(const FGameplayAbilitySpecHandle& SpecHandle : *SpecOnWeapons)
			{
				FGameplayAbilitySpec* GameplayAbilitySpec = GASComponent->FindAbilitySpecFromHandle(SpecHandle);

				if(nullptr != GameplayAbilitySpec)
				{
					UBaseGameplayAbility* BaseGameplayAbility = Cast<UBaseGameplayAbility>(GameplayAbilitySpec->Ability);

					if(IsValid(BaseGameplayAbility))
					{
						if(BaseGameplayAbility->AbilityTags.HasTag(UAsadalGameplayTags::AttackStatusGameplayTag))
						{
							PlayerSkillSet.Add(SpecHandle);
						}
					}
				}				
			}		
		}
	}
}

// Called when the game starts or when spawned
void APCCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::OneHandAxeTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::OneHandMaceTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::OneHandShieldTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::OneHandSwordTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::TwinHandBladeTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::TwinHandDaggerTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::TwoHandGreatswordTag);
	PlayerAnimationOnWeapons.Add(UAsadalGameplayTags::TwoHandShieldTag);

	TArray<const FGameplayAbilitySpec*> GameplayAbilitySpecs;
	
	GASComponent->GetAbilitySpecs(GameplayAbilitySpecs);

	for(const FGameplayAbilitySpec* AbilitySpec : GameplayAbilitySpecs)
	{
		UBaseGameplayAbility* BaseGameplayAbility = Cast<UBaseGameplayAbility>(AbilitySpec->Ability);

		for(auto& PlayerAnimationOnWeapon : PlayerAnimationOnWeapons)
		{
			if(BaseGameplayAbility->HasTagActivationRequiredTags(PlayerAnimationOnWeapon.Key))
			{
				PlayerAnimationOnWeapon.Value.Add(AbilitySpec->Handle);				
			}
		}
	}

	for(TSubclassOf<UAsadalInventoryItemDefinition> AsadalInventoryItemDefinitionClass : EquipmentWeaponItemDefinitionClasses)
	{
		EquipmentWeaponItemDefinitions.Add(NewObject<UAsadalInventoryItemDefinition>(this, AsadalInventoryItemDefinitionClass));
	}

	TryEquipNextWeapon();
}

// Called every frame
void APCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APCCharacter::__OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData)
{
	if(OverlapEventData.Caller->IsA(ABaseWeapon::StaticClass()))
	{
		//여기서부터 공격이 시작된다.
		if(OverlapEventData.OtherActor.IsValid())
		{
			GASComponent->GEToTarget(OverlapEventData.OtherActor.Get(), UAsadalGameplayTags::EventAttackBasicTag);
		}
	}
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
