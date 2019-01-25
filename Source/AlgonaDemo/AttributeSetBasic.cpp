// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeSetBasic.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"


UAttributeSetBasic::UAttributeSetBasic()
	: MaxHealth(100.f),
	Health (100.f),
	Mana(100.f),
	MaxMana(100.f)

{

}

void UAttributeSetBasic::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{ //health
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBasic::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBasic, Health))) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Health.GetCurrentValue());
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		OnHealthChange_del.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}//mana
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBasic::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBasic, Mana))) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Health.GetCurrentValue());
		Mana.SetCurrentValue(FMath::Clamp(Mana.GetCurrentValue(), 0.f, MaxMana.GetCurrentValue()));
		OnManaChange_del.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	}
	
}

void UAttributeSetBasic::ResetAttributs()
{
	Health.SetCurrentValue(MaxHealth.GetCurrentValue());
	Mana.SetCurrentValue(MaxMana.GetCurrentValue()); 
	OnManaChange_del.Broadcast(Mana.GetCurrentValue(), MaxMana.GetCurrentValue());
	OnHealthChange_del.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
}


