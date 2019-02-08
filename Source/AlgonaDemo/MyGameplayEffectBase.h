// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MyGameplayEffectBase.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UMyGameplayEffectBase : public UGameplayEffect
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Abilitybase")
		float GetDuration();
	
};
