// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/TimerManager.h"
#include "RPG_PlayerController.generated.h"

USTRUCT(BlueprintType)
struct FSkillCoolDown
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int IdSpellBook = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CoolDown = 0.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrCoolDown = 0.f;

};

/**
 * 
 */
UCLASS()
class ALGONADEMO_API ARPG_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void CD_Tick();

	FTimerHandle CD_Timer;

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<FSkillCoolDown> SkillsOnCD;
	UFUNCTION(BlueprintCallable)
		void AddSkillOnCD(FSkillCoolDown SkillOnCoolDown);
	UPROPERTY(BlueprintReadWrite)
		float TestRep = 0.f;

	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckIsOnCD(int IDSpellBook);
};
