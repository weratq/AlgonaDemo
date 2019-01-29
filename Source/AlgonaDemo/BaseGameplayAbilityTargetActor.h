// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "BaseGameplayAbilityTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API ABaseGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
	
public:
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;

	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
		bool GetPlayerLookingPoint(OUT FVector& OutViewPoint );

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		float Radius;
};
