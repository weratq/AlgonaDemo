// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilityTabs.h"


/*AAbilityTabs::AAbilityTabs()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAbilityTabs::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAbilityTabs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

FGameplayAbilityInfo::FGameplayAbilityInfo()
	:CooldownDuration(0.f),
	Cost(0.f),
	CostType(EAbilityCostType::Mana),
	UIMat(nullptr),
	AbilityClass(nullptr)
{
}

FGameplayAbilityInfo::FGameplayAbilityInfo(float InCooldownDuration, float InCost, EAbilityCostType InCostType, UMaterialInstance * InUIMat, TSubclassOf<class UBaseGameplayAbility> InAbilityClass, TArray<F_GA_LevelEffects> LevelEffectInfo)
	:CooldownDuration(InCooldownDuration),
	Cost(InCost),
	CostType(InCostType),
	UIMat(InUIMat),
	AbilityClass(InAbilityClass),
	LevelEffectInfo(LevelEffectInfo)
{
}