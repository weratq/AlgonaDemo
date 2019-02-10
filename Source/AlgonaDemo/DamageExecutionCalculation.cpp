// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageExecutionCalculation.h"
#include "AttributeSetBasic.h"

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritMelee)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, WeaponDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, CritMelee, Source, true);
	}
};

static DamageStatics& GetDamageStatics() 
{
	static DamageStatics DamageStaticVar;

	return DamageStaticVar;
}


UDamageExecutionCalculation::UDamageExecutionCalculation()
{
	HealthProperty = FindFieldChecked<UProperty>(UAttributeSetBasic::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBasic, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().WeaponDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritMeleeDef);

}

bool ShouldHappen(int percentage)
{
	return (FMath::RandRange(1, 100 / percentage) == 1 ? true : false);
}


void UDamageExecutionCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	float Strength = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().StrengthDef, FAggregatorEvaluateParameters(), Strength);
	float WeaponDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().WeaponDamageDef, FAggregatorEvaluateParameters(), WeaponDamage);
	float CritMelee = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().CritMeleeDef, FAggregatorEvaluateParameters(), CritMelee);
	float ArmorMagnitude = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().ArmorDef, FAggregatorEvaluateParameters(), ArmorMagnitude);

	//calculation + ((Strength/100) *WeaponDamage)
	UE_LOG(LogTemp, Warning, TEXT("%f"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("%f"), WeaponDamage);
	UE_LOG(LogTemp, Warning, TEXT("%f"), CritMelee);
	UE_LOG(LogTemp, Warning, TEXT("%f"), ArmorMagnitude);
	float FinalDamage = FMath::Clamp(WeaponDamage + ((Strength / 100) *WeaponDamage) - ArmorMagnitude , 0.f, 9999.f);
	
	if (CritMelee != 0) 
	{
		if (ShouldHappen(CritMelee * 100))
		{
			FinalDamage *= 2.f;
		}
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData (HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
