// Fill out your copyright notice in the Description page of Project Settings.

#include "RPG_PlayerController.h"




void ARPG_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CD_Timer, this, &ARPG_PlayerController::CD_Tick, 0.1, true, 0.1);
}

void ARPG_PlayerController::CD_Tick(void) {

	for (int i = 0; i != SkillsOnCD.Num(); i++) {
		if (SkillsOnCD[i].CurrCoolDown > 0) 
		{
			SkillsOnCD[i].CurrCoolDown -= 0.1f;
		}
	else
		{
			SkillsOnCD.RemoveAt(i);
		}
	}
}

void ARPG_PlayerController::AddSkillOnCD(FSkillCoolDown SkillOnCoolDown)
{
	SkillsOnCD.Add(SkillOnCoolDown);
}

bool ARPG_PlayerController::CheckIsOnCD(int IDSpellBook)
{
	for (int i = 0; i != SkillsOnCD.Num(); i++) 
	{
		if (SkillsOnCD[i].IdSpellBook == IDSpellBook) {
			return false;
		}
	}
	return true;
}

