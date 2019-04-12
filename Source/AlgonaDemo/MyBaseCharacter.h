// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Engine/Public/TimerManager.h"
#include "AttributeSetBasic.h"
#include "Abilites/DotGameplayEffectUIData.h"
#include "MyBaseCharacter.generated.h"



USTRUCT(BlueprintType)
struct FBP_DotInfo
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP_DotInfoStruct")
		int IdAppliedEffect;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP_DotInfoStruct")
		UMaterialInstance* EffectIcon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP_DotInfoStruct")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BP_DotInfoStruct")
		const UGameplayEffect* Def;
};


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


				/*-----On attribute change-----*/
	UFUNCTION()
		void OnHelthChanged(float Health, float MaxHealth);
	UFUNCTION()
		void OnManaChanged(float Mana, float MaxMana);
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHealthChange"))
		void BP_OnHelthChange(float Health, float MaxHealth);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnManaChange"))
		void BP_OnManaChange(float Mana, float MaxMana);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnRageChange"))
		void BP_OnRageChange(float Rage, float MaxRage);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnSpeedChange"))
		void BP_OnSpeedChange(float Rage, float MaxRage);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "SpawnDamageWidget"))
		void SpawnDamageWidget(float Damage);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnDie"))
		void BP_OnDie();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "CharBase")
		bool IsInOtherTeam(AMyBaseCharacter* OtherChar);
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void CharDie();
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void Restartg();
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void ApplyGESpecHandleToTargetSpecHandle( const FGameplayEffectSpecHandle& GESpecHandle,const FGameplayAbilityTargetDataHandle& TargetDataHandle );
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void SetPlayerAttribute(
			float MaxHEalth, float MaxMana, float Strength,
			float Inteligence, float Agility, float Spirit, 
			float Armor, float CritMelee, float CritMagic,
			float WeaponDamage);
	UFUNCTION(BlueprintCallable, Category = "CharBase")
		void AddEffectWhithCount(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext,int Count);
	

	FVector StartLocation;
UFUNCTION(BlueprintCallable)
	void OnEffectAdd(UAbilitySystemComponent * Target, const FGameplayEffectSpec & SpecApplied, FActiveGameplayEffectHandle ActiveHandle);
UFUNCTION(BlueprintCallable)
	void OnEffectRemoved(const FActiveGameplayEffect& Effect);

		/* Delegates */
	FDelegateHandle OnEffectAddDelegateHandle;
	
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "AddDotToUI"))
		void BP_AddDotToUI(FBP_DotInfo DotData);
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "RemoveDotFromUI"))
		void BP_RemvoeDotFromUI(FBP_DotInfo DotData);
		
	TArray<FBP_DotInfo> DotInfoArr;

protected:
	bool bIsDie = false;
	uint8 TeamID;
	void AutoDeterminTeamIDByContRollerType();
	
};