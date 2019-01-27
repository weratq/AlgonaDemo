// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseGameplayAbility.h"
#include "AbilityBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UAbilityBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
		UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Ability")
		FGameplayAbilityInfo GetAbilityInfoFromClass(TSubclassOf<UBaseGameplayAbility> AbilityClass);
	
	
};
