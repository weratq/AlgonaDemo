// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectUIData.h"
#include "Engine/Classes/Materials/MaterialInstance.h"
#include "DotGameplayEffectUIData.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UDotGameplayEffectUIData : public UGameplayEffectUIData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstance* IconMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float TimeDuration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Stack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Description;
};
