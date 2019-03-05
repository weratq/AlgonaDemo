// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor.h"
#include "Components/DecalComponent.h"
#include "AIGroundAbilityTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API AAIGroundAbilityTargetActor : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()
	
public:
	AAIGroundAbilityTargetActor();
		virtual void ConfirmTargetingAndContinue() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true))
		AActor* ActorToIgnore = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UDecalComponent* Decal;
	UPROPERTY(VisibleAnywhere)
		USceneComponent* Root;
};
