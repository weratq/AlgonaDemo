// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityBlueprintFunctionLibrary.h"

FGameplayAbilityInfo UAbilityBlueprintFunctionLibrary::GetAbilityInfoFromClass(TSubclassOf<UBaseGameplayAbility> AbilityClass)
{
	if (AbilityClass) {
		UBaseGameplayAbility* CurrAbility = AbilityClass->GetDefaultObject<UBaseGameplayAbility>();

		return CurrAbility->GetAbilityInfo();
	}

	return FGameplayAbilityInfo();
}
