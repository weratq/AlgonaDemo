// Fill out your copyright notice in the Description page of Project Settings.

#include "AttributeSetBasic.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"


UAttributeSetBasic::UAttributeSetBasic()
	: MaxHealth(100.f),
	Health (100.f)
{

}

void UAttributeSetBasic::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data)
{ 
	if (Data.EvaluatedData.Attribute.GetUProperty() == FindFieldChecked<UProperty>(UAttributeSetBasic::StaticClass(), GET_MEMBER_NAME_CHECKED(UAttributeSetBasic, Health))) {
		//UE_LOG(LogTemp, Warning, TEXT("%f"), Health.GetCurrentValue());
		Health.SetCurrentValue(FMath::Clamp(Health.GetCurrentValue(), 0.f, MaxHealth.GetCurrentValue()));
		OnHealthChnge_del.Broadcast(Health.GetCurrentValue(), MaxHealth.GetCurrentValue());
	}

	
}
