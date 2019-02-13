// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_BloodThrirstCalculation.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UGE_BloodThrirstCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGE_BloodThrirstCalculation();

		void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
