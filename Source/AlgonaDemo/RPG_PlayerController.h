// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/World.h"
#include "MyBaseCharacter.h"
#include "RPG_PlayerController.generated.h"



USTRUCT(BlueprintType)
struct FLernedAbility
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		int id;
	UPROPERTY(BlueprintReadWrite)
		int CurrLevel;
	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<class UBaseGameplayAbility> AbilityClass;
};


/**
 * 
 */
UCLASS()
class ALGONADEMO_API ARPG_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARPG_PlayerController();
	
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:



	virtual void SetupInputComponent() override;

	AMyBaseCharacter* Character;
	
		/*BUIND INPUT*/
	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeLeft();
	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeRight();
	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeBack();




				/*PlyerAbility managment*/
	UPROPERTY(BlueprintReadWrite, Category = "PlyerAbility")
		TArray <FLernedAbility> PlayerSkills;
	UFUNCTION(BlueprintCallable)
		void LearnAbility(FLernedAbility Skill);
	UFUNCTION(BlueprintCallable)
		void LevelUpAbilityByClass(TSubclassOf<UBaseGameplayAbility> AbilityClass);


};
