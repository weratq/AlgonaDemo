// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "UObject/Object.h"
#include "UObject/ObjectMacros.h"
#include "AttributeSetBasic.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFloatChngeDelegate, float, Health, float, MaxHealth);

UCLASS()
class ALGONADEMO_API UAttributeSetBasic : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSetBasic();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	FGameplayAttributeData Health;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData MaxHealth;

	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	FOnFloatChngeDelegate OnHealthChnge_del;

};
