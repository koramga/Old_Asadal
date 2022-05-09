// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "Asadal/GAS/AttributeSet/BaseCharacterAttributeSet.h"

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

void ABaseCharacter::InitializeAbility(TSubclassOf<UGameplayAbility> AbilityToGet, int32 AbilityLevel)
{
	if(IsValid(GASComponent))
	{
		if(HasAuthority() && IsValid(AbilityToGet))
		{
			GASComponent->GiveAbility(FGameplayAbilitySpec(AbilityToGet, AbilityLevel, 0));
		}

		GASComponent->InitAbilityActorInfo(this, this);
	}
}

void ABaseCharacter::GetHealthValues(float& Health, float& MaxHealth)
{
	if(IsValid(BaseCharacterAttributeSet))
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
	if(IsValid(BaseCharacterAttributeSet))
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
		GASComponent->SetTagMapCount(TagToAdd, 1);
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

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(GASComponent))
	{
		BaseCharacterAttributeSet = GASComponent->GetSet<UBaseCharacterAttributeSet>();

		if(IsValid(BaseCharacterAttributeSet))
		{
			GASComponent->GetGameplayAttributeValueChangeDelegate(BaseCharacterAttributeSet->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::__OnHealthChangedNative);
			GASComponent->GetGameplayAttributeValueChangeDelegate(BaseCharacterAttributeSet->GetManaAttribute()).AddUObject(this, &ABaseCharacter::__OnManaChangedNative);			
		}		
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
}

void ABaseCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
}

void ABaseCharacter::__OnHealthChangedNative(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data);
}

void ABaseCharacter::__OnManaChangedNative(const FOnAttributeChangeData& Data)
{
	OnManaChanged(Data);
}
