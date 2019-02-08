// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "GA_TargetActor_GetAround.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API AGA_TargetActor_GetAround : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
public:
		void StartTargeting(UGameplayAbility* Ability) override;
		void ConfirmTargetingAndContinue() override;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
			float Radius;

	
};
