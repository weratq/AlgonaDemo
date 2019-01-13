// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AttributeSetBasic.generated.h"

/**
 * 
 */
UCLASS()
class ALGONADEMO_API UAttributeSetBasic : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAttributeSetBasic();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
	FGameplayAttributeData Health;
};
