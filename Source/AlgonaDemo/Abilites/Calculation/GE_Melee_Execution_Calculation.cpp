// Fill out your copyright notice in the Description page of Project Settings.

#include "GE_Melee_Execution_Calculation.h"
#include "AttributeSetBasic.h"

struct DamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Strength)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health)
	DECLARE_ATTRIBUTE_CAPTUREDEF(MaxHealth)
	DECLARE_ATTRIBUTE_CAPTUREDEF(WeaponDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritMelee)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellBonusDamage)
	DamageStatics() {
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Strength, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, Health, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBasic, MaxHealth, Target, false);
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


UGE_Melee_Execution_Calculation::UGE_Melee_Execution_Calculation()
{
	HealthProperty = FindFieldChecked<UProperty>(UAttributeSetBasic::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBasic, Health));
	HealthDef = FGameplayEffectAttributeCaptureDefinition(HealthProperty, EGameplayEffectAttributeCaptureSource::Target, true);

	RelevantAttributesToCapture.Add(HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().StrengthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().WeaponDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().CritMeleeDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().SpellBonusDamageDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().HealthDef);
	RelevantAttributesToCapture.Add(GetDamageStatics().MaxHealthDef);

}




void UGE_Melee_Execution_Calculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
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
	float TargetHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().HealthDef, FAggregatorEvaluateParameters(), TargetHealth);
	float TargetMaxHealth = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetDamageStatics().MaxHealthDef, FAggregatorEvaluateParameters(), TargetMaxHealth);

	//calculation + ((Strength/100) *WeaponDamage)
	/*UE_LOG(LogTemp, Warning, TEXT("%f"), Strength);
	UE_LOG(LogTemp, Warning, TEXT("%f"), WeaponDamage);
	UE_LOG(LogTemp, Warning, TEXT("%f"), CritMelee);
	UE_LOG(LogTemp, Warning, TEXT("%f"), ArmorMagnitude);*/
	float AllDamage = 0.f;
	AllDamage = WeaponDamage + Strength;
	AllDamage *= SpellBonusDamage;

	if (TargetMaxHealth != 0)
	{
		float CalculateHealth;
		CalculateHealth = TargetHealth / TargetMaxHealth;
		if (CalculateHealth <= 0.2f)
		{
			UE_LOG(LogTemp, Warning, TEXT("DubleDamage"));
			AllDamage *= 2;
		}
	}
	float FinalDamage = FMath::Clamp(AllDamage - ArmorMagnitude, 0.f, 9999.f);

	

	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(HealthProperty, EGameplayModOp::Additive, -FinalDamage));
}

