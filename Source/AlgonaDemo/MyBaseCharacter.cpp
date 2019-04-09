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
	CharAttribute->OnRageChange_del.AddDynamic(this, &AMyBaseCharacter::BP_OnRageChange);
	AutoDeterminTeamIDByContRollerType();
	OnEffectAddDelegateHandle = AbilitySystemComp->OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &AMyBaseCharacter::OnEffectAdd);
	//StartLocation = GetActorLocation();
	AbilitySystemComp->OnAnyGameplayEffectRemovedDelegate().AddUObject(this, &AMyBaseCharacter::OnEffectRemoved);
	
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
	UDotGameplayEffectUIData* DotUIData;
	DotUIData = Cast<UDotGameplayEffectUIData>(SpecApplied.Def->UIData);
	if (DotUIData)
	{
		
		FBP_DotInfo DotInfo;
		DotInfo.Def = SpecApplied.Def;
		DotInfo.Duration = SpecApplied.Duration;
		DotInfo.EffectIcon = DotUIData->IconMaterial;
		DotInfoArr.Add(DotInfo);

		BP_AddDotToUI(DotInfo);
	}
}

void AMyBaseCharacter::OnEffectRemoved(const FActiveGameplayEffect & Effect)
{
	UE_LOG(LogTemp, Warning, TEXT("EffectRemoved"));

	UDotGameplayEffectUIData* CurrDot;
		CurrDot = Cast<UDotGameplayEffectUIData>(Effect.Spec.Def->UIData);
	if (CurrDot)
	{
		for (int32 i = 0; i < DotInfoArr.Num(); ++i)
		{
			if (DotInfoArr[i].Def == Effect.Spec.Def)
			{
				BP_RemvoeDotFromUI(DotInfoArr[i]);
				DotInfoArr.RemoveAt(i);
				return;
			}
		}	
	}	
}




