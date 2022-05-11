﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Asadal/Actor/Equipment/Weapon/BaseWeapon.h"
#include "Asadal/GAS/AttributeSet/BaseCharacterAttributeSet.h"
#include "Asadal/Animation/Instance/BaseAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GASComponent = CreateDefaultSubobject<UGASComponent>("GASComponent"); 
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GASComponent;
}

FGameplayAbilitySpecHandle ABaseCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	FGameplayAbilitySpecHandle AbilitySpecHandle;

	if(IsValid(GASComponent))
	{
		if(HasAuthority() && IsValid(AbilityToGet))
		{
			AbilitySpecHandle = GASComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}

		GASComponent->InitAbilityActorInfo(this, this);
	}
	
	return AbilitySpecHandle;
}

void ABaseCharacter::GetHealthValues(float& Health, float& MaxHealth)
{
	if(BaseCharacterAttributeSet.IsValid())
	{
		Health = BaseCharacterAttributeSet->GetHealth();
		MaxHealth = BaseCharacterAttributeSet->GetMaxHealth();		
	}
}

void ABaseCharacter::SetHealthValues(float NewHealth, float NewMaxHealth)
{
	if(IsValid(GASComponent))
	{
		GASComponent->ApplyModToAttribute(BaseCharacterAttributeSet->GetHealthAttribute(), EGameplayModOp::Override, NewHealth);
		GASComponent->ApplyModToAttribute(BaseCharacterAttributeSet->GetMaxHealthAttribute(), EGameplayModOp::Override, NewMaxHealth);		
	}
}

void ABaseCharacter::GetManaValues(float& Mana, float& MaxMana)
{
	if(BaseCharacterAttributeSet.IsValid())
	{
		Mana = BaseCharacterAttributeSet->GetMana();
		MaxMana = BaseCharacterAttributeSet->GetMaxMana();		
	}
}

void ABaseCharacter::SetManaValues(float NewMana, float NewMaxMana)
{
	if(IsValid(GASComponent))
	{
		GASComponent->ApplyModToAttribute(BaseCharacterAttributeSet->GetManaAttribute(), EGameplayModOp::Override, NewMana);
		GASComponent->ApplyModToAttribute(BaseCharacterAttributeSet->GetMaxManaAttribute(), EGameplayModOp::Override, NewMaxMana);		
	}
}

void ABaseCharacter::ChangeAbilityLevelWithTags(FGameplayTagContainer TagContainer, int32 NewAbilityLevel)
{
	if(IsValid(GASComponent))
	{
		TArray<FGameplayAbilitySpec*> MatchingAbilities;

		GASComponent->GetActivatableGameplayAbilitySpecsByAllMatchingTags(TagContainer, MatchingAbilities, true);

		for(FGameplayAbilitySpec* AbilitySpec : MatchingAbilities)
		{
			AbilitySpec->Level = NewAbilityLevel;
		}
	}
}

void ABaseCharacter::CancelAbilityWithTags(FGameplayTagContainer WithTags, FGameplayTagContainer WithoutTags)
{
	if(IsValid(GASComponent))
	{
		GASComponent->CancelAbilities(&WithTags, &WithoutTags, nullptr);
	}
}

void ABaseCharacter::AddLooseGameplayTag(FGameplayTag TagToAdd)
{
	if(IsValid(GASComponent))
	{
		GASComponent->AddLooseGameplayTag(TagToAdd);
		//GASComponent->SetTagMapCount(TagToAdd, 1);
	}
}

void ABaseCharacter::RemoveLooseGameplayTag(FGameplayTag TagToRemove)
{
	if(IsValid(GASComponent))
	{
		GASComponent->RemoveLooseGameplayTag(TagToRemove);
	}
}

void ABaseCharacter::ApplyGEToTargetData(const FGameplayEffectSpecHandle& GESpec,
	const FGameplayAbilityTargetDataHandle& TargetDataHandle)
{
	for(TSharedPtr<FGameplayAbilityTargetData> Data : TargetDataHandle.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpec.Data.Get());
	}
}

void ABaseCharacter::SetActivateCollision(const FString& Name, bool bIsActivate)
{
}

void ABaseCharacter::SetActivateEquipment(FGameplayTag GameplayTag, bool bIsActivate)
{
}

void ABaseCharacter::SetupWeapons()
{
	SetEquipWepaon(false);
	
	BaseWeapons.Empty();
	
	TArray<UActorComponent*> ActorComponents;
	GetComponents(UChildActorComponent::StaticClass(),ActorComponents);

	for(UActorComponent* ActorComponent : ActorComponents)
	{
		UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(ActorComponent);

		if(IsValid(ChildActorComponent))
		{
			if(ChildActorComponent->GetChildActor()->IsA(ABaseWeapon::StaticClass()))
			{
				//우선 Weapon에 담는다.
				BaseWeapons.Add(ChildActorComponent);
				ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(ChildActorComponent->GetChildActor());

				if(IsValid(BaseWeapon))
				{
					BaseWeapon->OnEquipmentOverlapEvent.AddDynamic(this, &ABaseCharacter::__OnEquipmentOverlapEventNative);
				}
			}
		}
	}
	SetEquipWepaon(true);
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	
	if(IsValid(GASComponent))
	{
		BaseCharacterAttributeSet = GASComponent->GetSet<UBaseCharacterAttributeSet>();

		if(BaseCharacterAttributeSet.IsValid())
		{
			GASComponent->GetGameplayAttributeValueChangeDelegate(BaseCharacterAttributeSet->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::__OnHealthChangedNative);
			GASComponent->GetGameplayAttributeValueChangeDelegate(BaseCharacterAttributeSet->GetManaAttribute()).AddUObject(this, &ABaseCharacter::__OnManaChangedNative);			
		}		
	}

	SetupWeapons();
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	
	UCharacterMovementComponent* Movement = GetCharacterMovement();
	FVector Forward = GetActorForwardVector();
	FVector Velocity = Movement->Velocity;
	float Speed = Velocity.Size();
	float Angle = 0.f;

	if (Movement->IsMovingOnGround())
	{
		if (Speed > 0)
		{
			//https://amored8701.tistory.com/132

			//if (IsLockOn())
			//{
			//	FRotator Rotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), LockOnBaseCharacter->GetActorLocation());
			//
			//	SetActorRotation(Rotator.Quaternion());
			//
			//	vForward = Rotator.RotateVector(FVector::ForwardVector);
			//}

			Forward.Z = 0.f;
			Velocity.Z = 0.f;

			Forward.Normalize();
			Velocity.Normalize();

			float fDot = FVector::DotProduct(Forward, Velocity);
			float fAcosAngle = FMath::Acos(fDot);
			float fAngle = FMath::RadiansToDegrees(fAcosAngle);

			FVector vCross = FVector::CrossProduct(Forward, Velocity);

			if (vCross.Z < 0)
			{
				//fAngle *= -1.f;
				fAngle = 360 - fAngle;
			}

			//Angle = fAngle + QUARTER_VIEW_ANGLE;

			//UE_LOG(LogTemp, Display, TEXT("Angle : %.2f"), fAngle);
		}

		if (BaseAnimInstance.IsValid())
		{
			//if (EMoveType::Run == MoveType)
			//{
			//	Ratio = 1.f;
			//}
			//else if (EMoveType::Sprint == MoveType)
			//{
			//	Ratio = 1.5f;
			//}
			BaseAnimInstance->SetSpeed(Speed / GetCharacterMovement()->GetMaxSpeed() * MoveBlendRatio);
			BaseAnimInstance->SetAngle(Angle);
		}
	}
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	UE_LOG(LogTemp, Display, TEXT("<%s> Health Change From %.2f To %.2f"), *GetName(), Data.OldValue, Data.NewValue);
}

void ABaseCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
}

void ABaseCharacter::SetEquipWepaon(bool bIsEquip)
{
	for(TSoftObjectPtr<UChildActorComponent> ChildActorComponent : BaseWeapons)
	{
		if(ChildActorComponent->GetChildActor()->IsA(ABaseWeapon::StaticClass()))
		{
			ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(ChildActorComponent->GetChildActor());

			if(IsValid(BaseWeapon))
			{
				BaseWeapon->SetEquip(bIsEquip);
			}
		}
	}
}

void ABaseCharacter::__OnHealthChangedNative(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data);
}

void ABaseCharacter::__OnManaChangedNative(const FOnAttributeChangeData& Data)
{
	OnManaChanged(Data);
}

void ABaseCharacter::__OnEquipmentOverlapEventNative(FEquipmentOverlapEventData OverlapEventData)
{
	if(OverlapEventData.Caller->IsA(ABaseWeapon::StaticClass()))
	{
		//여기서부터 공격이 시작된다.
		if(OverlapEventData.OtherActor.IsValid())
		{
			FGameplayTag AttackEventGameplayTag = FGameplayTag::RequestGameplayTag(TEXT("Event.Attack.Basic"));

			if(AttackEventGameplayTag.IsValid())
			{
				FGameplayEventData GameplayEventData;
				GameplayEventData.Target = OverlapEventData.OtherActor.Get();

				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AttackEventGameplayTag, GameplayEventData);				
			}			
		}
	}
}
