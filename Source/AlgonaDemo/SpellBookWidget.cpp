// Fill out your copyright notice in the Description page of Project Settings.

#include "SpellBookWidget.h"

FGameplayAbilityInfo USpellBookWidget::GetAbilityInfoFromClass(TSubclassOf<UBaseGameplayAbility> AbilityClass)
{
	if (AbilityClass) {
		UBaseGameplayAbility* CurrAbility = AbilityClass->GetDefaultObject<UBaseGameplayAbility>();
		
		return CurrAbility->GetAbilityInfo();
	}

	return FGameplayAbilityInfo();
}
