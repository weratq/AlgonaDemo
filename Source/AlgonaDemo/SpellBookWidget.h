// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseGameplayAbility.h"
#include "SpellBookWidget.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API USpellBookWidget : public UUserWidget
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable,Category = "Spellbook")
		FGameplayAbilityInfo GetAbilityInfoFromClass(TSubclassOf<UBaseGameplayAbility> AbilityClass);
	
};
