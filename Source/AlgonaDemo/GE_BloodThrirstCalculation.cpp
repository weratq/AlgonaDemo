// Fill out your copyright notice in the Description page of Project Settings.

#include "GE_BloodThrirstCalculation.h"
#include "AttributeSetBasic.h"


struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);
	DamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, MaxHealth, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Health, Source, true);
	}
};

static DamageStatics& GetDamageStatics()
{
	static DamageStatics DamageStaticVar;

	return DamageStaticVar;
}



UGE_BloodThrirstCalculation::UGE_BloodThrirstCalculation()

{
	RelevantAttributesToCapture.Add(GetDamageStatics().MaxHealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().HealthDef);
}




void UGE_BloodThrirstCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	float MaxHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().MaxHealthDef, FAggregatorEvaluateParameters(), MaxHealth);

	float FinalHeal = 0.f;
	FinalHeal = MaxHealth * 0.06f;

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(GetDamageStatics().HealthProperty, EGameplayModOp::Additive, FinalHeal));
}