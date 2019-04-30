// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AbilityTabs.h"
#include "BaseGameplayAbility.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct F_GA_LevelEffectList
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		int NeedLevel = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityInfo")
		TSubclassOf<class UGameplayEffect> GamePlayEffect;

	F_GA_LevelEffects GetEffectInfo(F_GA_LevelEffectList Effect);
};
UCLASS()
class ALGONADEMO_API UBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
			UMaterialInstance* UIMaterial;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbilityBase")
			TArray<F_GA_LevelEffectList> LevelEffectList;
		UFUNCTION(BlueprintCallable, Category = "Abilitybase")
			FGameplayAbilityInfo GetAbilityInfo();
		
};
