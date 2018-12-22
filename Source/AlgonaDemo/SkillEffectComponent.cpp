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

	// ...

}


// Called every frame
void USkillEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float USkillEffectComponent::Dot(float tick, float TimeRemaiting) {
	
	UE_LOG(LogTemp, Warning, TEXT("hkfd"));
	return 12.f;

}

void USkillEffectComponent::ReturnDamage(void) {
	return;

}

void USkillEffectComponent::AddDot(FDotTickEffect DotToAdd) {

	if (DotToAdd.id != -1) {
		//ищем наложеный такой же дот
		for (int i = 0; i < DotOn.Num(); i++) {


			if (DotOn[i].id == DotToAdd.id){

			// стакаеться ли эфект?
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
	//UE_LOG(LogTmp, Warning, TEXT("Invalid dot Effect!!!"));
}


void USkillEffectComponent::RefreshDot(int IndexInDotOn) {
	DotOn[IndexInDotOn].TimeRemaiting = DotOn[IndexInDotOn].MaxTimeDuration;
}