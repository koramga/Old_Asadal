// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Asadal/Actor/Object/Equipment/Weapon/BaseWeapon.h"
#include "Asadal/GAS/AttributeSet/BaseCharacterAttributeSet.h"
#include "Asadal/GAS/AttributeSet/OffenseAttributeSet.h"
#include "Asadal/GAS/AttributeSet/DefenseAttributeSet.h"
#include "Asadal/GAS/AttributeSet/LifeAttributeSet.h"
#include "Asadal/Animation/Instance/BaseAnimInstance.h"
#include "Asadal/Actor/DamageText/TextActor.h"
#include "Asadal/Controller/PC/PCController.h"
#include "Asadal/Game/GameMode/MainGameMode.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"
#include "Asadal/GAS/AttributeSet/LifeAttributeSet.h"
#include "Asadal/Inventory/Fragment/InventoryFragment_EquippableItem.h"
#include "GameFramework/GameModeBase.h"

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
	if(LifeAttributeSet.IsValid())
	{
		Health = LifeAttributeSet->GetHealth();
		MaxHealth = LifeAttributeSet->GetMaxHealth();		
	}
}

void ABaseCharacter::SetHealthValues(float NewHealth, float NewMaxHealth)
{
	if(LifeAttributeSet.IsValid())
	{
		GASComponent->ApplyModToAttribute(LifeAttributeSet->GetHealthAttribute(), EGameplayModOp::Override, NewHealth);
		GASComponent->ApplyModToAttribute(LifeAttributeSet->GetMaxHealthAttribute(), EGameplayModOp::Override, NewMaxHealth);		
	}
}

void ABaseCharacter::GetManaValues(float& Mana, float& MaxMana)
{
	if(LifeAttributeSet.IsValid())
	{
		Mana = LifeAttributeSet->GetMana();
		MaxMana = LifeAttributeSet->GetMaxMana();		
	}
}

void ABaseCharacter::SetManaValues(float NewMana, float NewMaxMana)
{
	if(LifeAttributeSet.IsValid())
	{
		GASComponent->ApplyModToAttribute(LifeAttributeSet->GetManaAttribute(), EGameplayModOp::Override, NewMana);
		GASComponent->ApplyModToAttribute(LifeAttributeSet->GetMaxManaAttribute(), EGameplayModOp::Override, NewMaxMana);		
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

bool ABaseCharacter::HasMatchingGameplayTag(FGameplayTag Tag) const
{
	if(IsValid(GASComponent))
	{
		return GASComponent->HasMatchingGameplayTag(Tag);
	}

	return false;
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

void ABaseCharacter::LinkSubAnimInstance(const FGameplayTag& GameplayTag)
{
	TSubclassOf<UAnimInstance>* SubAnimInstanceClass = SubAnimInstanceClassMap.Find(GameplayTag);

	if(nullptr != SubAnimInstanceClass)
	{
		GetMesh()->LinkAnimClassLayers((*SubAnimInstanceClass));
	}
}


void ABaseCharacter::UnLinkSubAnimInstance(const FGameplayTag& GameplayTag)
{
	TSubclassOf<UAnimInstance>* SubAnimInstanceClass = SubAnimInstanceClassMap.Find(GameplayTag);

	if(nullptr != SubAnimInstanceClass)
	{
		GetMesh()->UnlinkAnimClassLayers((*SubAnimInstanceClass));
	}
}

void ABaseCharacter::SetActivateCollision(const FString& Name, bool bIsActivate)
{
}

void ABaseCharacter::TryActivateEquipment(const FGameplayTag& GameplayTag, bool bIsActivate)
{
}

void ABaseCharacter::SetEquipInventoryItem(TSoftObjectPtr<UAsadalInventoryItemDefinition> InventoryItemDefinition)
{
	UInventoryFragment_EquippableItem* FragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(InventoryItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

	if(IsValid(FragmentEquippableItem))
	{
		if(FragmentEquippableItem->HasGameplayTag(UAsadalGameplayTags::ItemWeaponTag))
		{
			//Weapon입니다.

			if(InventoryItemDefinition != EquipmentWepaonItemDefinition)
			{
				if(EquipmentWepaonItemDefinition.IsValid())
				{
					UInventoryFragment_EquippableItem* EquipmentFragmentEquippableItem = Cast<UInventoryFragment_EquippableItem>(EquipmentWepaonItemDefinition->FindFragmentByClass(UInventoryFragment_EquippableItem::StaticClass()));

					EquipmentFragmentEquippableItem->SetActivate(this, false);
				}

				if(IsValid(FragmentEquippableItem))
				{
					FragmentEquippableItem->SetActivate(this, true);
					const TArray<TSoftObjectPtr<ABaseEquipment>>& Equipments = FragmentEquippableItem->GetSpawnEquipmentActors();

					for(TSoftObjectPtr<ABaseEquipment> BaseEquipment : Equipments)
					{
						BaseEquipment->OnEquipmentOverlapEvent.AddDynamic(this, &ABaseCharacter::__OnEquipmentOverlapEventNative);
					}
				}

				EquipmentWepaonItemDefinition = InventoryItemDefinition;
			}
		}
	}
}

void ABaseCharacter::TryEquipNextWeapon()
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
			FGameplayTag AbilityGameplayTag = UAsadalGameplayTags::GetAbilityGameplayTagFromItem(EquipmentFragmentEquippableItem->GetItemGameplayTag());

			if(AbilityGameplayTag != FGameplayTag::EmptyTag)
			{
				GASComponent->SetActivateAbilityActionGroup(AbilityGameplayTag);
			}
		}
	}
}

void ABaseCharacter::TryAvoid()
{
	if(IsValid(GASComponent))
	{
		GASComponent->TryAvoidAbilityFromActionGroup();
	}
}

bool ABaseCharacter::IsDeath() const
{
	return HasMatchingGameplayTag(UAsadalGameplayTags::DeathActionGameplayTag);
	//return HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(TEXT("Character.Status.Death")));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
	BaseAnimInstance = Cast<UBaseAnimInstance>(GetMesh()->GetAnimInstance());
	
	if(IsValid(GASComponent))
	{
		GASComponent->OnGEToTargetLatentEvent.AddDynamic(this, &ABaseCharacter::__OnGEToTargetLatentEventNative);
		GASComponent->OnTagUpdatedEvent.AddDynamic(this, &ABaseCharacter::__OnTagUpdatedEventNative);
		
		// Init starting data
		for (int32 i=0; i < AttributeSets.Num(); ++i)
		{
			if (AttributeSets[i].Attributes && AttributeSets[i].DefaultStartingTable)
			{
				const UAttributeSet* Attributes = GASComponent->InitStats(AttributeSets[i].Attributes, AttributeSets[i].DefaultStartingTable);
			}
		}
		
		LifeAttributeSet = GASComponent->GetSet<ULifeAttributeSet>();

		if(LifeAttributeSet.IsValid())
		{
			GASComponent->GetGameplayAttributeValueChangeDelegate(LifeAttributeSet->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::__OnHealthChangedNative);
			GASComponent->GetGameplayAttributeValueChangeDelegate(LifeAttributeSet->GetManaAttribute()).AddUObject(this, &ABaseCharacter::__OnManaChangedNative);			
		}
		
		OffenseAttributeSet = GASComponent->GetSet<UOffenseAttributeSet>();
		DefenseAttributeSet = GASComponent->GetSet<UDefenseAttributeSet>();
	}

	DamageTextSpawnComponents.Empty();

	TArray<UActorComponent*> FindActorComponents;

	GetComponents(USceneComponent::StaticClass(), FindActorComponents);

	for(UActorComponent* ActorComponent : FindActorComponents)
	{
		if(DamageTextSpawnComponentNames.Contains(ActorComponent->GetName()))
		{
			USceneComponent* SceneComponent = Cast<USceneComponent>(ActorComponent);
		
			DamageTextSpawnComponents.Add(SceneComponent);			
		}		
	}
	
	for(int i = 0; i < AbilityClasses.Num(); ++i)
	{
		InitializeAbility(AbilityClasses[i], 0);
	}
	
	for(TSubclassOf<UAsadalInventoryItemDefinition> AsadalInventoryItemDefinitionClass : EquipmentWeaponItemDefinitionClasses)
	{
		EquipmentWeaponItemDefinitions.Add(NewObject<UAsadalInventoryItemDefinition>(this, AsadalInventoryItemDefinitionClass));
	}

	TryEquipNextWeapon();

	for(const FGameplayTag& LooseGameplayTag : AddLooseGameplayTagContainer)
	{
		AddLooseGameplayTag(LooseGameplayTag);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for(FMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
	{
		MaterialInstanceVariable.Update(GetMesh(), DeltaTime);
	}
		
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
	//UE_LOG(LogTemp, Display, TEXT("<%s> Health Change From %.2f To %.2f"), *GetName(), Data.OldValue, Data.NewValue);

	if(Data.NewValue <= 0.f)
	{
		if(false == IsDeath())
		{
			AddLooseGameplayTag(UAsadalGameplayTags::DeathActionGameplayTag);
			UpdateDeath(true);
		}
	}
	else
	{
		if(true == IsDeath())
		{
			RemoveLooseGameplayTag(UAsadalGameplayTags::DeathActionGameplayTag);
			UpdateDeath(false);
		}	
	}

	if(false == IsDeath())
	{		
		float DeltaValue = Data.NewValue - Data.OldValue; 

		if(DamageTextActorClasses.Num() > 0)
		{
			if(DeltaValue < 0)
			{				
				if(nullptr != Data.GEModData
					&& false == HasMatchingGameplayTag(UAsadalGameplayTags::HitStateGameplayTag))
				{
					OnHit(Data);
				}
			}

			if(false == FMath::IsNearlyEqual(DeltaValue, 0.f))
			{
				const UBaseGameplayAbility* GameplayAbility = Cast<UBaseGameplayAbility>(Data.GEModData->EffectSpec.GetEffectContext().GetAbilityInstance_NotReplicated());

				UGEExecResult* ExecResult = nullptr;
				
				if(IsValid(GameplayAbility))
				{
					ExecResult = Cast<UGEExecResult>(Data.GEModData->EffectSpec.GetEffectContext().GetSourceObject());
				}
				
				int32 Index =  FMath::RandRange(0, DamageTextActorClasses.Num() - 1);
		
				FActorSpawnParameters ActorSpawnParam;

				ActorSpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
				ActorSpawnParam.Owner = this;

				FVector DamageTextLocation = GetActorLocation();
				//FRotator DamageTextRotator = GetActorRotation();

				if(DamageTextSpawnComponents.Num() > 0)
				{
					int32 DamageTextSpawnComponentIndex =  FMath::RandRange(0, DamageTextSpawnComponents.Num() - 1);

					FTransform WorldTransform = DamageTextSpawnComponents[DamageTextSpawnComponentIndex]->GetComponentToWorld();

					DamageTextLocation = WorldTransform.GetLocation();
					//DamageTextRotator = WorldTransform.GetRotation().Rotator();
				}

				ATextActor* TextActor = GetWorld()->SpawnActor<ATextActor>(DamageTextActorClasses[Index], DamageTextLocation, FRotator::ZeroRotator, ActorSpawnParam);

					
				FColor Color = FColor::Black;
				FString Text = FString::Printf(TEXT("%.0f"), FMath::Abs(DeltaValue));
				
				if(IsValid(TextActor))
				{
					if(IsValid(ExecResult))
					{
						if(ExecResult->IsCritical())
						{
							Text = FString::Printf(TEXT("Critical"));
						}

						float FireDamage = ExecResult->GetDamage(UAsadalGameplayTags::AttributePropertyFireTag);
						float WaterDamage = ExecResult->GetDamage(UAsadalGameplayTags::AttributePropertyWaterTag);
						float TreeDamage = ExecResult->GetDamage(UAsadalGameplayTags::AttributePropertyTreeTag);

						Color = FColor::Red;
						
						if(WaterDamage > FireDamage
							&& WaterDamage > TreeDamage)
						{
							Color = FColor::Blue;
						}
						else if(TreeDamage > FireDamage
							&& TreeDamage > WaterDamage)
						{
							Color = FColor::Green;
						}						
					}
					else
					{
						if(DeltaValue > 0)
						{
							Color = FColor::Blue;
						}						
					}
					
					TextActor->SetText(Text, Color);			
				}	
			}			
		}
	}
}

void ABaseCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
}

void ABaseCharacter::UpdateDeath(bool bIsDeath)
{
	if(true == bIsDeath)
	{
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);		
	}
	else
	{
		
	}
}

void ABaseCharacter::OnHit(const FOnAttributeChangeData& Data)
{
	if(GASComponent->TryHitAbilityFromActionGroup())
	{
		AActor* Actor = Data.GEModData->EffectSpec.GetEffectContext().GetInstigator();

		if(IsValid(Actor))
		{
			FVector TargetLocation = Actor->GetActorLocation();
			FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
			FRotator NewRotator = FRotator(GetActorRotation().Pitch, LookAtRotator.Yaw, GetActorRotation().Roll);
			
			SetActorRotation(NewRotator);
		}			
	}
	
	/*
	const FGameplayAbilityActionGroup* GameplayAbilityActionGroup = GASComponent->GetActivateAbilityActionGroup();

	if(nullptr != GameplayAbilityActionGroup)
	{
		if(GASComponent->TryActivateAbility(GameplayAbilityActionGroup->HitAbilitySpecHandle))
		{
			AActor* Actor = Data.GEModData->EffectSpec.GetEffectContext().GetInstigator();

			if(IsValid(Actor))
			{
				FVector TargetLocation = Actor->GetActorLocation();
				FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
				FRotator NewRotator = FRotator(GetActorRotation().Pitch, LookAtRotator.Yaw, GetActorRotation().Roll);
			
				SetActorRotation(NewRotator);
			}			
		}
	}
	*/
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

			if(OverlapEventData.OtherActor->GetClass()->ImplementsInterface(UAbilitySystemInterface::StaticClass()))
			{
				IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(OverlapEventData.OtherActor.Get());

				GASComponent->GEToTarget(AbilitySystemInterface->GetAbilitySystemComponent(), UAsadalGameplayTags::EventAttackBasicTag);
			}
		}
	}
}

void ABaseCharacter::__OnGEToTargetLatentEventNative(const TArray<FGEToTargetEventItem>& LatentEventItems, bool bIsCritical)
{
	if(LatentEventItems.Num() > 0)
	{
		//Latent Event로 무언가 공격을 했다.!

		APCController* PCController = Cast<APCController>(GetController());

		if(IsValid(PCController)
			&& PCController == GetWorld()->GetFirstPlayerController())
		{
			//플레이어가 직접 조종하고있다면
			AMainGameMode* MainGameMode = Cast<AMainGameMode>(GetWorld()->GetAuthGameMode());

			if(IsValid(MainGameMode))
			{
				MainGameMode->SetTimeDilationKeepTime(UAsadalGameplayTags::GameTimeDilationStrikeTag, PCController->GetStrikeTimeDilationSettings());
			}

			if(bIsCritical)
			{
				TSubclassOf<UCameraShakeBase> StrikeCameraShake = PCController->GetStrikeCameraShake();

				if(IsValid(StrikeCameraShake))
				{
					PCController->ClientStartCameraShake(StrikeCameraShake);
				}				
			}
		}
	}

	//UE_LOG(LogTemp, Display, TEXT("GEToTargetLatentEvent : <%d>"), LatentEventItem.Num());
}

void ABaseCharacter::__OnTagUpdatedEventNative(const FGameplayTag& GameplayTag, bool bIsActivate)
{
	if(UAsadalGameplayTags::HitStateGameplayTag == GameplayTag)
	{
		if(bIsActivate)
		{
			//Material Instance ON

			for(FMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
			{
				MaterialInstanceVariable.SetMaterialInstanceParameterWithBackup(GetMesh());
				MaterialInstanceVariable.StartUpdate();
			}
		}
		else
		{
			for(FMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
			{
				MaterialInstanceVariable.RollbackMaterialInstanceParameter(GetMesh());
				MaterialInstanceVariable.EndUpdate();
			}
			
			//Material Instance OFF
			//UMaterialInstanceDynamic* MaterialInstanceDynamic = GetMesh()->CreateDynamicMaterialInstance(0);
			//
			//if(IsValid(MaterialInstanceDynamic))
			//{
			//	MaterialInstanceDynamic->SetVectorParameterValue(TEXT("OutLineColor"), FLinearColor(1.f, 0.f, 0.f, 0.f));
			//}		
		}
	}
	else if(UAsadalGameplayTags::DeathStateGameplayTag == GameplayTag)
	{
		if(bIsActivate)
		{
			
		}
		else
		{
			
		}
	}
	
	UE_LOG(LogTemp, Display, TEXT("<%s> : <%d>"), *GameplayTag.ToString(),bIsActivate);
}
