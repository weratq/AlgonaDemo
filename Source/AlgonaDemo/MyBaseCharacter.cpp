// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBaseCharacter.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "BrainComponent.h"


// Sets default values
AMyBaseCharacter::AMyBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	CharAttribute = CreateDefaultSubobject<UAttributeSetBasic>("CharAttibut");
	TeamID = 255;

}

// Called when the game starts or when spawned
void AMyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	CharAttribute->OnHealthChnge_del.AddDynamic(this, &AMyBaseCharacter::OnHelthChanged);
	AutoDeterminTeamIDByContRollerType();
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

void AMyBaseCharacter::OnHelthChanged(float Health, float MaxHealth)
{
	if (Health <= 0.f&& !bIsDie)
	{
		BP_OnDie();
		CharDie();
		bIsDie = true;
	}
	BP_OnHelthChange(Health, MaxHealth);
}

bool AMyBaseCharacter::IsInOtherTeam(AMyBaseCharacter * OtherChar)
{
	return TeamID != OtherChar->TeamID;
}

void AMyBaseCharacter::CharDie()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC) {
		PC->DisableInput(PC);
	}
	AAIController* APC = Cast<AAIController>(GetController());
	if (APC) {
		APC->GetBrainComponent()->StopLogic("Death");
	}

}

void AMyBaseCharacter::AutoDeterminTeamIDByContRollerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}




