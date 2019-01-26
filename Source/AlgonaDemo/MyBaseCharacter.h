// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Engine/Public/TimerManager.h"
#include "AttributeSetBasic.h"
#include "MyBaseCharacter.generated.h"

//class UAttributeSetBasic;

UCLASS()
class ALGONADEMO_API AMyBaseCharacter : public ACharacter, public IAbilitySystemInterface
{	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DotTimer(float tick, float TimeRemaiting);

	void Test(void);
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "Ability")
		UAbilitySystemComponent* AbilitySystemComp = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
		UAttributeSetBasic* CharAttribute = nullptr;
	UFUNCTION(BlueprintCallable,Category = "CharAbility")
		void AddAbility(TSubclassOf<UGameplayAbility> AbilityToAdd);
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;

	UFUNCTION()
		void OnHelthChanged(float Health, float MaxHealth);
	UFUNCTION()
		void OnManaChanged(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChange"))
		void BP_OnHelthChange(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChange"))
		void BP_OnManaChange(float Mana, float MaxMana);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDie"))
		void BP_OnDie();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "CharBase")
		bool IsInOtherTeam(AMyBaseCharacter* OtherChar);
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void CharDie();
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void Restartg();
	FVector StartLocation;
protected:
	bool bIsDie = false;
	uint8 TeamID;
	void AutoDeterminTeamIDByContRollerType();

};