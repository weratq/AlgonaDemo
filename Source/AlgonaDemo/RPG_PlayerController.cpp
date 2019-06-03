// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_PlayerController.h"
#include "UnrealNetwork.h"


ARPG_PlayerController::ARPG_PlayerController() {
	SetReplicates(true);
}

void ARPG_PlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void ARPG_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	Character = Cast<AMyBaseCharacter>(GetPawn());
	if (Character == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("INVALID PAWN!"));
	}
}
void ARPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Dodge_Left", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeLeft);
	InputComponent->BindAction("Dodge_Right", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeRight);
	InputComponent->BindAction("Dodge_Back", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeBack);
 }



void ARPG_PlayerController::LearnAbility(FLernedAbility Skill)
{
	if (Skill.AbilityClass != nullptr&&GetPawn()!=nullptr)
	{
		Character->AddAbility(Skill.AbilityClass);
		PlayerSkills.Add(Skill);
	}
}



void ARPG_PlayerController::LevelUpAbilityByClass(TSubclassOf<UBaseGameplayAbility> AbilityClass)
{
	if (AbilityClass != nullptr)
	{
		FGameplayAbilitySpec* CurrAbility = Character->AbilitySystemComp->FindAbilitySpecFromClass(AbilityClass);
		if (CurrAbility != nullptr)
		{
			CurrAbility->Level++;
			return;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Skill Level UP Fail"));
}

int ARPG_PlayerController::GetAbilityLevelByClass(TSubclassOf<UBaseGameplayAbility> AbilityClass)
{
	if (AbilityClass != nullptr)
	{
		FGameplayAbilitySpec* CurrAbility = Character->AbilitySystemComp->FindAbilitySpecFromClass(AbilityClass);
		if (CurrAbility != nullptr)
		{			
			return CurrAbility->Level;
		}
		
	}
	return 0;
}






