// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseCharacter.h"


// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharAttribute = CreateDefaultSubobject<UAttributeSetBasic>("CharAttibut");
}

// Called when the game starts or when spawned
void AMyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyBaseCharacter::DotTimer(float tick, float TimeRemaiting) {
	FTimerHandle Timer;
	//GetWorldTimerManager().SetTimer(Timer,this, &AMyBaseCharacter::DotTimer, false, tick);

}

void AMyBaseCharacter::Test(void) {

}

void AMyBaseCharacter::AddAbility(TSubclassOf<UGameplayAbility> AbilityToAdd)
{
	if (AbilitySystemComp) {
		if (HasAuthority() && AbilityToAdd)
		{
			AbilitySystemComp->GiveAbility(FGameplayAbilitySpec(AbilityToAdd, 1, 0));
		}
		AbilitySystemComp->InitAbilityActorInfo(this, this);
	}
}

UAbilitySystemComponent * AMyBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComp;
}
