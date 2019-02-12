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
	CharAttribute->OnHealthChange_del.AddDynamic(this, &AMyBaseCharacter::OnHelthChanged);
	CharAttribute->OnManaChange_del.AddDynamic(this, &AMyBaseCharacter::OnManaChanged);
	AutoDeterminTeamIDByContRollerType();

	//StartLocation = GetActorLocation();
	
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

void AMyBaseCharacter::OnManaChanged(float Mana, float MaxMana)
{
	BP_OnManaChange(Mana, MaxMana);
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
		//Restart();
	}
	AAIController* APC = Cast<AAIController>(GetController());
	if (APC) {
		APC->GetBrainComponent()->StopLogic("Death");
	}

}

void AMyBaseCharacter::Restartg()
{
	//SetActorLocation(StartLocation, false, nullptr, ETeleportType::ResetPhysics);
	//CharAttribute->ResetAttributs();
}

void AMyBaseCharacter::ApplyGESpecHandleToTargetSpecHandle(const FGameplayEffectSpecHandle & GESpecHandle, const FGameplayAbilityTargetDataHandle & TargetDataHandle)
{
	for (TSharedPtr<FGameplayAbilityTargetData> Data : TargetDataHandle.Data)
	{
		Data->ApplyGameplayEffectSpec(*GESpecHandle.Data.Get());
	}
}

void AMyBaseCharacter::SetPlayerAttribute(float MaxHEalth, float MaxMana, float Strength, float Inteligence, float Agility, float Spirit, float Armor, float CritMelee, float CritMagic,float WeaponDamage)
{	
	CharAttribute->MaxHealth.SetCurrentValue(MaxHEalth);
	CharAttribute->MaxMana.SetCurrentValue(MaxMana);
	/*CharAttribute->Strength.SetBaseValue(Strength);
	CharAttribute->Strength.SetCurrentValue(Strength);
	CharAttribute->Inteligence.SetBaseValue(Inteligence);
	CharAttribute->Inteligence.SetCurrentValue(Inteligence);
	CharAttribute->Agility.SetBaseValue(Agility);
	CharAttribute->Agility.SetCurrentValue(Agility);
	CharAttribute->Spirit.SetBaseValue(Spirit);
	CharAttribute->Spirit.SetCurrentValue(Spirit);
	CharAttribute->Armor.SetBaseValue(Armor);
	CharAttribute->Armor.SetCurrentValue(Armor);
	CharAttribute->CritMelee.SetBaseValue(CritMelee);
	CharAttribute->CritMelee.SetCurrentValue(CritMelee);
	CharAttribute->CritMagic.SetBaseValue(CritMagic);
	CharAttribute->CritMagic.SetCurrentValue(CritMagic);
	CharAttribute->WeaponDamage.SetBaseValue(WeaponDamage);
	CharAttribute->WeaponDamage.SetCurrentValue(WeaponDamage);*/
	OnHelthChanged(CharAttribute->Health.GetCurrentValue(), MaxHEalth);
	OnManaChanged(CharAttribute->Mana.GetCurrentValue(), MaxMana);
}

void AMyBaseCharacter::AddEffectWhithCount(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level, FGameplayEffectContextHandle EffectContext,int Count)
{
	for (int i = 0; i < Count; ++i)
	{
		AbilitySystemComp->BP_ApplyGameplayEffectToSelf(GameplayEffectClass, Level, EffectContext);
	}
	
}

void AMyBaseCharacter::AutoDeterminTeamIDByContRollerType()
{
	if (GetController() && GetController()->IsPlayerController())
	{
		TeamID = 0;
	}
}

void AMyBaseCharacter::OnEffectAdd(UAbilitySystemComponent * Target, const FGameplayEffectSpec & SpecApplied, FActiveGameplayEffectHandle ActiveHandle)
{
	UE_LOG(LogTemp, Warning, TEXT("hgdlfg"));
}




