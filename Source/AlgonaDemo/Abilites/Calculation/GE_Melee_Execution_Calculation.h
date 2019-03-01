// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GE_Melee_Execution_Calculation.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UGE_Melee_Execution_Calculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UGE_Melee_Execution_Calculation();
	UProperty* HealthProperty;
	FGameplayEffectAttributeCaptureDefinition HealthDef;
		void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const;
};
