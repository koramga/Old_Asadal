// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGEExec.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "../AttributeSet/LifeAttributeSet.h"
#include "Asadal/GAS/Ability/BaseGameplayAbility.h"
#include "Asadal/GAS/AttributeSet/DefenseAttributeSet.h"
#include "Asadal/GAS/AttributeSet/OffenseAttributeSet.h"
#include "Asadal/Utility/GameplayTag/AsadalGameplayTags.h"

UBaseGEExec::UBaseGEExec()
{
	DEFINE_ATTRIBUTE_CAPTUREDEF(ULifeAttributeSet, Health, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(ULifeAttributeSet, Mana, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(ULifeAttributeSet, Shield, Target, true);
	
	DEFINE_ATTRIBUTE_CAPTUREDEF(UDefenseAttributeSet, BaseResistance, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UDefenseAttributeSet, WaterResistance, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UDefenseAttributeSet, TreeResistance, Target, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UDefenseAttributeSet, FireResistance, Target, true);
	
	DEFINE_ATTRIBUTE_CAPTUREDEF(UOffenseAttributeSet, BaseDamageBuff, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UOffenseAttributeSet, WaterDamageBuff, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UOffenseAttributeSet, FireDamageBuff, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UOffenseAttributeSet, TreeDamageBuff, Source, true);
	DEFINE_ATTRIBUTE_CAPTUREDEF(UOffenseAttributeSet, CriticalRate, Source, true);
	
	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(ManaDef);
	RelevantAttributesToCapture.Add(ShieldDef);

	RelevantAttributesToCapture.Add(BaseResistanceDef);
	RelevantAttributesToCapture.Add(WaterResistanceDef);
	RelevantAttributesToCapture.Add(TreeResistanceDef);
	RelevantAttributesToCapture.Add(FireResistanceDef);

	RelevantAttributesToCapture.Add(BaseDamageBuffDef);
	RelevantAttributesToCapture.Add(WaterDamageBuffDef);
	RelevantAttributesToCapture.Add(FireDamageBuffDef);
	RelevantAttributesToCapture.Add(TreeDamageBuffDef);
	RelevantAttributesToCapture.Add(CriticalRateDef);

	ValidTransientAggregatorIdentifiers.AddTag(UAsadalGameplayTags::AttributePropertyFireTag);
	ValidTransientAggregatorIdentifiers.AddTag(UAsadalGameplayTags::AttributePropertyTreeTag);
	ValidTransientAggregatorIdentifiers.AddTag(UAsadalGameplayTags::AttributePropertyWaterTag);
}

void UBaseGEExec::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                         FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	const FGameplayEffectSpec& GameplayEffectSpec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle GameplayEffectContextHandle = GameplayEffectSpec.GetContext();
	const UBaseGameplayAbility* ConstBaseGameplayAbility = Cast<UBaseGameplayAbility>(GameplayEffectContextHandle.GetAbilityInstance_NotReplicated());
	UBaseGameplayAbility* BaseGameplayAbility = const_cast<UBaseGameplayAbility*>(ConstBaseGameplayAbility);

	float Shield = 0.f;
	float Health = 0.f;
	float Mana = 0.f;
	
	float FireDamage = 0.f;
	float WaterDamage = 0.f;
	float TreeDamage = 0.f;

	float FireBuffDamage = 0.f;
	float WaterBuffDamage = 0.f;
	float TreeBuffDamage = 0.f;

	float BaseDamageBuff = 0.f;
	float FireDamageBuff = 0.f;
	float WaterDamageBuff = 0.f;
	float TreeDamageBuff = 0.f;

	float BaseResistance = 0.f;
	float FireResistance = 0.f;
	float TreeResistance = 0.f;
	float WaterResistance = 0.f;

	float CriticalRate = 0.f;

	float OutShield = 0.f;
	float OutHealth = 0.f;

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(HealthDef, FAggregatorEvaluateParameters(), Health);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ShieldDef, FAggregatorEvaluateParameters(), Shield);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(ManaDef, FAggregatorEvaluateParameters(), Mana);
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(BaseResistanceDef, FAggregatorEvaluateParameters(), BaseResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FireResistanceDef, FAggregatorEvaluateParameters(), FireResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TreeResistanceDef, FAggregatorEvaluateParameters(), TreeResistance);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(WaterResistanceDef, FAggregatorEvaluateParameters(), WaterResistance);

	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(BaseDamageBuffDef, FAggregatorEvaluateParameters(), BaseDamageBuff);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(WaterDamageBuffDef, FAggregatorEvaluateParameters(), WaterDamageBuff);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(TreeDamageBuffDef, FAggregatorEvaluateParameters(), TreeDamageBuff);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(FireDamageBuffDef, FAggregatorEvaluateParameters(), FireDamageBuff);
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CriticalRateDef, FAggregatorEvaluateParameters(), CriticalRate);
	
	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(UAsadalGameplayTags::AttributePropertyFireTag, FAggregatorEvaluateParameters(), FireDamage);
	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(UAsadalGameplayTags::AttributePropertyWaterTag, FAggregatorEvaluateParameters(), WaterDamage);
	ExecutionParams.AttemptCalculateTransientAggregatorMagnitude(UAsadalGameplayTags::AttributePropertyTreeTag, FAggregatorEvaluateParameters(), TreeDamage);

	if(!FMath::IsNearlyEqual(BaseDamageBuff, 0.f))
	{
		FireBuffDamage += (FireDamage * BaseDamageBuff);
		WaterBuffDamage += (WaterDamage * BaseDamageBuff);
		TreeBuffDamage += (TreeDamage * BaseDamageBuff);
	}

	if(!FMath::IsNearlyEqual(FireDamageBuff, 0.f))
	{
		FireBuffDamage += (FireDamage * FireDamageBuff);
	}

	if(!FMath::IsNearlyEqual(WaterDamageBuff, 0.f))
	{
		WaterBuffDamage += (WaterDamage * WaterDamageBuff);
	}

	if(!FMath::IsNearlyEqual(TreeDamageBuff, 0.f))
	{
		TreeBuffDamage += (TreeDamage * TreeDamageBuff);
	}

	float FinalFireDamage = FMath::Clamp(FireDamage + FireBuffDamage - FireResistance - BaseResistance, 0.f, FLT_MAX);
	float FinalWaterDamage = FMath::Clamp(WaterDamage + WaterBuffDamage - WaterResistance - BaseResistance, 0.f, FLT_MAX);
	float FinalTreeDamage = FMath::Clamp(TreeDamage + TreeBuffDamage - TreeResistance - BaseResistance, 0.f, FLT_MAX);

	bool bIsCritical = false;

	float Rand = FMath::RandRange(0.f, 1.f);

	if(Rand <= CriticalRate)
	{
		bIsCritical = true;
	}

	if(bIsCritical)
	{
		FinalFireDamage *= 2.f;
		FinalWaterDamage *= 2.f;
		FinalTreeDamage *= 2.f;
	}

	float OffenseDamage = FinalFireDamage + FinalWaterDamage + FinalTreeDamage;
	
	OutShield = Shield - OffenseDamage;

	if(OutShield < 0.f)
	{
		OutHealth = Health - abs(OutShield);
		OutShield = 0.f;

		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ShieldProperty, EGameplayModOp::Override, OutShield));
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Override, OutHealth));		
	}
	else
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ShieldProperty, EGameplayModOp::Override, OutShield));
	}

	if(IsValid(BaseGameplayAbility))
	{
		FGameplayEffectContext* EffectContext = GameplayEffectContextHandle.Get();

		UGEExecResult* GEExecResult = NewObject<UGEExecResult>();
		
		EffectContext->AddSourceObject(GEExecResult);
		GEExecResult->SetCritical(bIsCritical);
		GEExecResult->SetDamage(UAsadalGameplayTags::AttributePropertyFireTag, FinalFireDamage);
		GEExecResult->SetDamage(UAsadalGameplayTags::AttributePropertyWaterTag, FinalWaterDamage);
		GEExecResult->SetDamage(UAsadalGameplayTags::AttributePropertyTreeTag, FinalTreeDamage);

		BaseGameplayAbility->AddAbilityGEExecInfo(GEExecResult);
	}

	/*
	FGameplayTag CueGameplayTag = FGameplayTag::RequestGameplayTag("GameplayCue.Hit.Normal");

	
	FGameplayCueParameters Parameters(GameplayEffectContextHandle);

	Parameters.Instigator = GameplayEffectContextHandle.GetInstigator();
	Parameters.RawMagnitude = OffenseDamage;

	if(nullptr != GameplayEffectContextHandle.GetHitResult())
	{
		Parameters.Location = GameplayEffectContextHandle.GetHitResult()->Location;
		Parameters.Normal = GameplayEffectContextHandle.GetHitResult()->Normal;		
	}
	
	Parameters.AbilityLevel = GameplayEffectContextHandle.GetAbilityLevel();
	Parameters.EffectCauser = GameplayEffectContextHandle.GetEffectCauser();
	Parameters.EffectContext = GameplayEffectContextHandle;
	Parameters.NormalizedMagnitude = 0.f;
	Parameters.OriginalTag = CueGameplayTag;
	Parameters.GameplayEffectLevel = GameplayEffectSpec.GetLevel();
		
	ExecutionParams.GetTargetAbilitySystemComponent()->ExecuteGameplayCue(CueGameplayTag, Parameters);
	*/
}
