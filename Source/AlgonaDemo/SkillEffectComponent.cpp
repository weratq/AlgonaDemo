// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillEffectComponent.h"


// Sets default values for this component's properties
USkillEffectComponent::USkillEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillEffectComponent::BeginPlay()
{
	Super::BeginPlay();
GetOwner()->GetWorldTimerManager().SetTimer(MainDotTimer, this, &USkillEffectComponent::Dot, 0.1, true,0.1);
	// ...

}


// Called every frame
void USkillEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

void USkillEffectComponent::Dot(void) {
	

	if (DotOn.IsValidIndex(0))
	{
		float TotalDamageInTick = 0;

		for (int i = 0; i < DotOn.Num(); i++) {

			if (DotOn[i].TimeLeftToNextTick <= 0) {
				TotalDamageInTick += DotOn[i].Damage * DotOn[i].StackCount;
				DotOn[i].TimeLeftToNextTick += DotOn[i].TickTime;
				DotOn[i].TimeRemaiting -= 0.1f;
				
			}
			else
			{
				DotOn[i].TimeRemaiting -= 0.1f;
				DotOn[i].TimeLeftToNextTick -= 0.1f;
				
			}
			if (DotOn[i].TimeRemaiting <= 0) {
				DotOn.RemoveAt(i);
				OnChangeDotArr.Broadcast();
			}

		}
		
		ReturnDamage(TotalDamageInTick);
	}
	
	

}

float USkillEffectComponent::ReturnDamage(float Damage) {

	FDamageEvent DamageEvent;
	GetOwner()->TakeDamage(Damage,DamageEvent , nullptr, nullptr);
	return Damage;

	
}

void USkillEffectComponent::AddDot(FDotTickEffect DotToAdd) {

	if (DotToAdd.id != -1) {
		//ищем наложеный такой же дот
		for (int i = 0; i < DotOn.Num(); i++) {


			if (DotOn[i].id == DotToAdd.id){

			
				if (DotToAdd.IsStack) {
			//если можно стакать то добавлям +1 стак
					if (DotOn[i].MaxStackCount > DotOn[i].StackCount) {
						DotOn[i].StackCount++;
							return;
					}
					// при максимальных скаках обновляем эфект
					RefreshDot(i);
					return;
				}
				// если нходим уже тикающий,обновляем
				RefreshDot(i);
				return;	
			}
			
		}

		DotOn.Add(DotToAdd);
		OnChangeDotArr.Broadcast();
		return;
	}

}


void USkillEffectComponent::RefreshDot(int IndexInDotOn) {
	DotOn[IndexInDotOn].TimeRemaiting = DotOn[IndexInDotOn].MaxTimeDuration;
}