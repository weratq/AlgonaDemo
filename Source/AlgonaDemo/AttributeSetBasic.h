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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Mana;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData MaxMana;
	void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Inteligence;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Strength;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Agility;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Spirit;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData Armor;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData CritMelee;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData CritMagic;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		FGameplayAttributeData WeaponDamage;

	UFUNCTION(BlueprintCallable, Category = "CharBase")
	void ResetAttributs();

	FOnFloatChngeDelegate OnHealthChange_del;
	FOnFloatChngeDelegate OnManaChange_del;

};
