// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityTabs.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
		UMaterialInstance* UIMaterial;
	
		UFUNCTION(BlueprintCallable, Category = "Abilitybase")
			FGameplayAbilityInfo GetAbilityInfo();
		
};
