// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAbilitySystemComponent.h"
#include "UObject/UObjectHash.h"
#include "UObject/UObjectIterator.h"
#include "Engine/Canvas.h"
#include "DisplayDebugHelpers.h"
#include "Engine/Engine.h"
#include "GameFramework/HUD.h"
#include "AbilitySystemStats.h"
#include "AbilitySystemGlobals.h"
#include "GameplayCueManager.h"

#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "GameplayEffectCustomApplicationRequirement.h"
#include "TimerManager.h"



void UMyAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();

	// Cache net role here as well since for map-placed actors on clients, the Role may not be set correctly yet in OnRegister.
	//CacheIsNetSimulated();
	OnGameplayEffectAppliedDelegateToTarget.AddUObject(this, &UMyAbilitySystemComponent::OnEffectAdd);
}

void UMyAbilitySystemComponent::OnEffectAdd(UAbilitySystemComponent * Target, const FGameplayEffectSpec & SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("hgdlfg"));
}
