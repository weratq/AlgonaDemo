// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Engine/Public/TimerManager.h"
#include "Engine/World.h"
#include "RPG_PlayerController.generated.h"

//Client side for widgets
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
//Server side changed only when sombody ask
USTRUCT()
struct FServerSkillCD
{
	GENERATED_BODY()
	UPROPERTY()
		int id = -1;
	UPROPERTY()
		float CDDuration = 0.f;
	UPROPERTY()
		float StartTimeInSec = 0.f;

};


USTRUCT(BlueprintType)
struct FLernedAbility
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		int id;
	UPROPERTY(BlueprintReadWrite)
		int CurrLevel;
	UPROPERTY(BlueprintReadWrite)
		TSubclassOf<class ABaseGameplayAbility> AbilityClass;
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
	UPROPERTY(BlueprintReadWrite)
	TArray<FSkillCoolDown> SkillsOnCD;

	UFUNCTION(BlueprintCallable)
		void AddSkillOnCD(FSkillCoolDown SkillOnCoolDown);
	UPROPERTY(BlueprintReadWrite)
		float TestRep = 0.f;

	
UFUNCTION(BlueprintCallable)
	void CD_TickClient();

	FTimerHandle CD_Timer;
	// server functions 
	UFUNCTION(BlueprintCallable)
		void RepFunction();
	TArray<FServerSkillCD> TServerSkillsCD;
	UFUNCTION(Server, Reliable, WithValidation)
		void Server_AddSkillOnCD(FServerSkillCD SkillToAdd);

	virtual void SetupInputComponent() override;

		FServerSkillCD ConvertToServerSt(FSkillCoolDown InputCD);
		//return true if not on CD
	UFUNCTION(BlueprintCallable, BlueprintPure)
		bool CheckIsOnCD(int IDSpellBook);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetSpellCD_Left(int IDSpellBook);

	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeLeft();
	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeRight();
	UFUNCTION(BlueprintImplementableEvent, Category = "InputAction")
		void BP_DodgeBack();




				/*PlyerAbility managment*/
	UPROPERTY(BlueprintReadWrite, Category = "PlyerAbility")
		TArray <FLernedAbility> PlayerSkills;
	UFUNCTION(BlueprintCallable, Categoty = "PlayerAbility")
		void LearnAbility(FLernedAbility Skill);


};
