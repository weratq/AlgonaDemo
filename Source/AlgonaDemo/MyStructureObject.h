// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyStructureObject.generated.h"


USTRUCT(BlueprintType)
		struct FDotTickEffect
	{
	GENERATED_BODY()

			UPROPERTY(EditAnywhere, BlueprintReadWrite)
			int id = -1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float TimeRemaiting = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float TickTime = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float Damage = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			bool IsStack = false;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			int StackCount = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			int MaxStackCount = 1;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float MaxTimeDuration = 0.f;
		UPROPERTY(EditAnywhere, BlueprintReadWrite)
			float TimeLeftToNextTick = 0.f;
	};
/**
 * 


 */
UCLASS()
class ALGONADEMO_API UMyStructureObject : public UObject
{
	GENERATED_BODY()
	
	
	
	
};
	