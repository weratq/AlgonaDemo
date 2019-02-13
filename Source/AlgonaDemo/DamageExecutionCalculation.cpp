// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageExecutionCalculation.h"
#include "AttributeSetBasic.h"

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritMelee)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellBonusDamage)
	DamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, WeaponDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, CritMelee, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, SpellBonusDamage, Source, true);
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
	RelevantAttributesToCapture.Add(GetDamageStatics().SpellBonusDamageDef);

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
	float SpellBonusDamage = 1.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().SpellBonusDamageDef, FAggregatorEvaluateParameters(), SpellBonusDamage);

	//calculation + ((Strength/100) *WeaponDamage)
	/*UE_LOG(LogTemp, Warning, TEXT("%f"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("%f"), WeaponDamage);
	UE_LOG(LogTemp, Warning, TEXT("%f"), CritMelee);
	UE_LOG(LogTemp, Warning, TEXT("%f"), ArmorMagnitude);*/
	float AllDamage = 0.f;
	AllDamage = WeaponDamage + Strength;
	AllDamage *= SpellBonusDamage;

	float FinalDamage = FMath::Clamp(AllDamage  - ArmorMagnitude , 0.f, 9999.f);
	
	if (CritMelee != 0) 
	{
		
	}

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData (HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}
