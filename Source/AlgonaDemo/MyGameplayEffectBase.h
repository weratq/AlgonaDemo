// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "MyGameplayEffectBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType) 
enum class EDamageType : uint8
{
	DT_Physic UMETA(DisplayName = "Physic"),
	DT_Magic UMETA(DisplayName = "Magic"),
	DT_Clean UMETA(DisplayName = "Clean")
};


UCLASS()
class ALGONADEMO_API UMyGameplayEffectBase : public UGameplayEffect
{
	GENERATED_BODY()

		UFUNCTION(BlueprintCallable, Category = "Abilitybase")
		float GetDuration();
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "GameplayEffect")
		EDamageType DamageType;
};
