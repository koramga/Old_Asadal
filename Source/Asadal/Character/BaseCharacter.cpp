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
#include "Asadal/Controller/NPC/NPCController.h"
#include "Asadal/Controller/PC/PCController.h"
#include "Asadal/Game/GameMode/MainGameMode.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"
#include "Asadal/GAS/AttributeSet/LifeAttributeSet.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Asadal/Widget/Screen/ScreenCharacterStatusWidget.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GASComponent = CreateDefaultSubobject<UGASComponent>("GASComponent");
	BaseEquipmentComponent = CreateDefaultSubobject<UBaseEquipmentComponent>("EquipmentComponent");
	BaseInventoryComponent = CreateDefaultSubobject<UBaseInventoryComponent>("InventoryComponent");
	BaseBTComponent = CreateDefaultSubobject<UBaseBTComponent>("BTComponent");
	
	if(IsValid(GASComponent))
	{
		BaseEquipmentComponent->SetKRGAbilitySystemComponent(GASComponent);
		BaseInventoryComponent->SetKRGAbilitySystemComponent(GASComponent);
		BaseBTComponent->SetKRGAbilitySystemComponent(GASComponent);
	}

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	
	//Arm을 Root에 붙여준다.
	SpringArmComponent->SetupAttachment(RootComponent);

	//Camera를 Arm에 붙여준다.
	CameraComponent->SetupAttachment(SpringArmComponent);

	SpringArmComponent->SetActive(false);
	CameraComponent->SetActive(false);
}

UAbilitySystemComponent* ABaseCharacter::GetAbilitySystemComponent() const
{
	return GASComponent;
}

UKRGGASBTComponent* ABaseCharacter::GetKRGGASBTComponent() const
{
	return BaseBTComponent;
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

UTexture2D* ABaseCharacter::GetAbilityIconByIndex(int32 Index)
{
	const FGameplayAbilityActionGroup* AbilityActionGroup = GASComponent->GetActivateAbilityActionGroup();
	
	if(nullptr != AbilityActionGroup
		&& AbilityActionGroup->AttackAbilityFragmentHandles.Num() > Index)
	{
		return AbilityActionGroup->AttackAbilityFragmentHandles[Index].KRGGASAbilityInfo->IconTexture;
	}

	return nullptr;
}

void ABaseCharacter::SetActivateCollision(const FString& Name, bool bIsActivate)
{
}

void ABaseCharacter::TryActivateEquipment(const FGameplayTag& GameplayTag, bool bIsActivate)
{
	UKRGGASItem* Item = BaseEquipmentComponent->GetItemFromEquipmentGameplayTag(UAsadalGameplayTags::EquipmentWeaponTag);

	if(IsValid(Item))
	{
		TArray<TSoftObjectPtr<AActor>>& SpawnActors = Item->GetSpawnActors();

		for(TSoftObjectPtr<AActor> SpawnEquipmentActor : SpawnActors)
		{
			ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(SpawnEquipmentActor.Get());

			if(IsValid(BaseWeapon))
			{
				BaseWeapon->SetActivateCollision(bIsActivate);
			}
		}
	}
}

void ABaseCharacter::TryEquipNextWeapon()
{	
	if(IsDeath())
	{
		return;
	}

	if(BaseEquipmentComponent->EquipmentNextExtraItem(UAsadalGameplayTags::EquipmentWeaponTag))
	{
		UKRGGASItem* Item = BaseEquipmentComponent->GetItemFromEquipmentGameplayTag(UAsadalGameplayTags::EquipmentWeaponTag);

		if(IsValid(Item))
		{
			TArray<TSoftObjectPtr<AActor>>& SpawnActors = Item->GetSpawnActors();

			for(TSoftObjectPtr<AActor> SpawnEquipmentActor : SpawnActors)
			{
				ABaseWeapon* BaseWeapon = Cast<ABaseWeapon>(SpawnEquipmentActor.Get());

				if(IsValid(BaseWeapon))
				{
					BaseWeapon->OnEquipmentOverlapEvent.AddDynamic(this, &ABaseCharacter::__OnEquipmentOverlapEventNative);
				}
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

bool ABaseCharacter::TryAttackAbilityByIndex(int32 Index)
{
	return GASComponent->TryAttackAbilityFromActionGroup(Index);
}

void ABaseCharacter::InputMoveForward(float Value)
{
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

void ABaseCharacter::InputMoveRight(float Value)
{
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
		GASComponent->OnGEExecLatentEvent.AddDynamic(this, &ABaseCharacter::__OnGEToTargetLatentEventNative);
		GASComponent->OnTagUpdatedEvent.AddDynamic(this, &ABaseCharacter::__OnTagUpdatedEventNative);

		GASComponent->ActivateFragmentAttributeSet(UAsadalGameplayTags::AttributeFragmentDefaultTag);
		LifeAttributeSet = GASComponent->GetSet<ULifeAttributeSet>();

		if(LifeAttributeSet.IsValid())
		{
			GASComponent->GetGameplayAttributeValueChangeDelegate(LifeAttributeSet->GetHealthAttribute()).AddUObject(this, &ABaseCharacter::__OnHealthChangedNative);
			GASComponent->GetGameplayAttributeValueChangeDelegate(LifeAttributeSet->GetManaAttribute()).AddUObject(this, &ABaseCharacter::__OnManaChangedNative);			
		}
		
		OffenseAttributeSet = GASComponent->GetSet<UOffenseAttributeSet>();
		DefenseAttributeSet = GASComponent->GetSet<UDefenseAttributeSet>();
	}

	if(IsValid(BaseInventoryComponent)
		&& IsValid(BaseEquipmentComponent))
	{
		TArray<TSoftObjectPtr<UKRGGASItem>> KRGGASWeaponItems = BaseInventoryComponent->GetItemsFromTag(UAsadalGameplayTags::ItemWeaponTag);
		
		for(TSoftObjectPtr<UKRGGASItem> WeaponItem : KRGGASWeaponItems)
		{
			if(false == BaseEquipmentComponent->AddExtraItem(WeaponItem.Get()))
			{
				UE_LOG(LogTemp, Display, TEXT("AddExtraItem Failed"));
			}
		}
	}

	TryEquipNextWeapon();

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

	for(const FGameplayTag& LooseGameplayTag : AddLooseGameplayTagContainer)
	{
		AddLooseGameplayTag(LooseGameplayTag);
	}
	
	TArray<UActorComponent*> ActorComponents;
	
	GetComponents(UWidgetComponent::StaticClass(), ActorComponents);

	for(UActorComponent* ActorComponent : ActorComponents)
	{
		UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(ActorComponent);

		if(IsValid(WidgetComponent))
		{
			if(WidgetComponent->GetWidget()->IsA(UScreenCharacterStatusWidget::StaticClass()))
			{
				ScreenCharacterStatusWidget = Cast<UScreenCharacterStatusWidget>(WidgetComponent->GetWidget());

				if(IsPossessedByPlayer())
				{
					ScreenCharacterStatusWidget->SetHiddenInGame(true);
				}
				
				UpdateCharacterStatusWidget();
				break;
			}
		}
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	for(FKRGMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
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

void ABaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	APCController* PCController = Cast<APCController>(NewController);
	ANPCController* NPCController = Cast<ANPCController>(NewController);
	
	if(IsValid(PCController))
	{
		//PCCharacter
		OnUpdatePossessedByPlayer(PCController);
	}
	else if(IsValid(NPCController))
	{
		OnUpdatePossessedByAI(NPCController);
	}
}

void ABaseCharacter::UnPossessed()
{
	Super::UnPossessed();

	OnUpdateUnPossessed();
}

void ABaseCharacter::OnHealthChanged(const FOnAttributeChangeData& Data)
{
	//UE_LOG(LogTemp, Display, TEXT("<%s> Health Change From %.2f To %.2f"), *GetName(), Data.OldValue, Data.NewValue);

	if(Data.NewValue <= 0.f)
	{
		if(false == IsDeath())
		{
			AddLooseGameplayTag(UAsadalGameplayTags::DeathStateGameplayTag);
			//UpdateDeath(true);
		}
	}
	else
	{
		if(true == IsDeath())
		{
			RemoveLooseGameplayTag(UAsadalGameplayTags::DeathStateGameplayTag);
			//UpdateDeath(false);
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

	UpdateCharacterStatusWidget();
}

void ABaseCharacter::OnManaChanged(const FOnAttributeChangeData& Data)
{
}

void ABaseCharacter::OnDeath(bool bIsDeath)
{
	if(IsPossessedByAI())
	{ 
		if(ScreenCharacterStatusWidget.IsValid())
		{
			ScreenCharacterStatusWidget->SetHiddenInGame(bIsDeath);
		}		
	}
	
	if(true == bIsDeath)
	{
		GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetPhysicsLinearVelocity(FVector::ZeroVector);
		AddLooseGameplayTag(UAsadalGameplayTags::DeathActionGameplayTag);
	}
	else
	{
		RemoveLooseGameplayTag(UAsadalGameplayTags::DeathActionGameplayTag);
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
}

void ABaseCharacter::OnTagUpdatedEvent(const FGameplayTag& GameplayTag, bool bIsActivate)
{	
	//이거 PC로 가야하는데 일단은 이대로 간다. (npc가 copy형태라서)
	if(GameplayTag.MatchesTag(UAsadalGameplayTags::AbilityGameplayTag))
	{
		if(bIsActivate)
		{
			if(GameplayTag != FGameplayTag::EmptyTag)
			{
				GASComponent->ActivateFragmentAbility(GameplayTag);
				LinkSubAnimInstance(GameplayTag);
			}		
		}
		else
		{
			if(GameplayTag != FGameplayTag::EmptyTag)
			{
				UnLinkSubAnimInstance(GameplayTag);
			}
		}
	}
	else if(UAsadalGameplayTags::HitStateGameplayTag == GameplayTag)
	{
		if(bIsActivate)
		{
			//Material Instance ON

			for(FKRGMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
			{
				MaterialInstanceVariable.SetMaterialInstanceParameterWithBackup(GetMesh());
				MaterialInstanceVariable.StartUpdate();
			}
		}
		else
		{
			for(FKRGMaterialInstanceVariable& MaterialInstanceVariable : HitMaterialInstanceVairables)
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
		OnDeath(bIsActivate);
	}
		UE_LOG(LogTemp, Display, TEXT("OnTagUpdatedEvent : <%s> : <%d>"), *GameplayTag.ToString(),bIsActivate);
}

void ABaseCharacter::OnUpdatePossessedByPlayer(APCController* PCController)
{
	CameraComponent->SetActive(true);
	SpringArmComponent->SetActive(true);

	if(ScreenCharacterStatusWidget.IsValid())
	{
		ScreenCharacterStatusWidget->SetHiddenInGame(true);
	}
}

void ABaseCharacter::OnUpdatePossessedByAI(ANPCController* NPCController)
{
	CameraComponent->SetActive(false);
	SpringArmComponent->SetActive(false);

	if(ScreenCharacterStatusWidget.IsValid())
	{
		ScreenCharacterStatusWidget->SetHiddenInGame(false);
	}

	BaseBTComponent->SetBlackboardData(NPCController);	
}

void ABaseCharacter::OnUpdateUnPossessed()
{
	CameraComponent->SetActive(false);
	SpringArmComponent->SetActive(false);

	if(ScreenCharacterStatusWidget.IsValid())
	{
		ScreenCharacterStatusWidget->SetHiddenInGame(true);
	}	
}

void ABaseCharacter::UpdateCharacterStatusWidget()
{
	if(ScreenCharacterStatusWidget.IsValid())
	{
		float Health, MaxHealth;
		GetHealthValues(Health, MaxHealth);

		ScreenCharacterStatusWidget->SetHealthPercent(Health / MaxHealth);		
	}	
}

bool ABaseCharacter::IsPossessedByPlayer() const
{
	if(IsValid(Cast<APCController>(Controller)))
	{
		return true;
	}

	return false;
}

bool ABaseCharacter::IsPossessedByAI() const
{
	if(IsValid(Cast<ANPCController>(Controller)))
	{
		return true;
	}

	return false;
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

				GASComponent->GEExecToTarget(AbilitySystemInterface->GetAbilitySystemComponent(), UAsadalGameplayTags::EventAttackBasicTag);
			}
		}
	}
}

void ABaseCharacter::__OnGEToTargetLatentEventNative(const TArray<FGEEExecEvent>& GEExecEvents, bool bIsCritical)
{
	if(GEExecEvents.Num() > 0)
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
	OnTagUpdatedEvent(GameplayTag, bIsActivate);
}
