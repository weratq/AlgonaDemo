// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Components/DecalComponent.h"
#include "BaseGameplayAbilityTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API ABaseGameplayAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
	
public:
	ABaseGameplayAbilityTargetActor();
	virtual void StartTargeting(UGameplayAbility* Ability) override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;
	UFUNCTION(BlueprintCallable, Category = "GroundSelect")
		bool GetPlayerLookingPoint(FVector& OutViewPoint );

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (ExposeOnSpawn = true))
		float Radius;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
		UDecalComponent* Decal;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector ViewPoint;
};
