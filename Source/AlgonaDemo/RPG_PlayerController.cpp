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
	
		GetWorldTimerManager().SetTimer(CD_Timer, this, &ARPG_PlayerController::CD_TickClient, 0.1, true, 0.1);
	
}
void ARPG_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Dodge_Left", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeLeft);
	InputComponent->BindAction("Dodge_Right", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeRight);
	InputComponent->BindAction("Dodge_Back", IE_DoubleClick, this, &ARPG_PlayerController::BP_DodgeBack);
 }


void ARPG_PlayerController::CD_TickClient(void) {
	
	if (SkillsOnCD.IsValidIndex(0)) {
		for (int i = 0; i < SkillsOnCD.Num(); i++) {
			if (SkillsOnCD[i].CurrCoolDown > 0)
			{
				SkillsOnCD[i].CurrCoolDown -= 0.1f;
			}
			if (SkillsOnCD[i].CurrCoolDown<=0)
			{
				SkillsOnCD.RemoveAt(i);
			}
		}
	}
}

void ARPG_PlayerController::AddSkillOnCD(FSkillCoolDown SkillOnCoolDown)
{
	SkillOnCoolDown.CurrCoolDown = SkillOnCoolDown.CoolDown;
	//UE_LOG(LogTemp,Warning,TEXT("CUrrCD %f" ),SkillOnCoolDown.CurrCoolDown)
	SkillsOnCD.Add(SkillOnCoolDown);
	Server_AddSkillOnCD(ConvertToServerSt(SkillOnCoolDown));

}
//return true if not on CD
bool ARPG_PlayerController::CheckIsOnCD(int IDSpellBook)
{
	for (int i = 0; i < SkillsOnCD.Num(); i++)
	{
		if (SkillsOnCD[i].IdSpellBook == IDSpellBook) {
			return false;
		}
	}
	return true;
}

float ARPG_PlayerController::GetSpellCD_Left(int IDSpellBook)
{
	float CD = 0.f;
	for (int i = 0; i < SkillsOnCD.Num(); i++)
	{
		if (SkillsOnCD[i].IdSpellBook == IDSpellBook) {
			return SkillsOnCD[i].CurrCoolDown;
		}
	}
	return CD;
}



void ARPG_PlayerController::RepFunction(void)
{
	
}

void ARPG_PlayerController::Server_AddSkillOnCD_Implementation(FServerSkillCD SkillToAdd)
{
	SkillToAdd.StartTimeInSec = GetWorld()->TimeSeconds;
	TServerSkillsCD.Add(SkillToAdd);

}
bool ARPG_PlayerController::Server_AddSkillOnCD_Validate(FServerSkillCD SkillToAdd) {
	return true;
}

FServerSkillCD ARPG_PlayerController::ConvertToServerSt(FSkillCoolDown InputCD)
{
	FServerSkillCD ServerCD;
	if (InputCD.IdSpellBook != -1)
	{
		ServerCD.CDDuration = InputCD.CoolDown;
		ServerCD.id = InputCD.IdSpellBook;
		return ServerCD;
	}
	return FServerSkillCD();
}


