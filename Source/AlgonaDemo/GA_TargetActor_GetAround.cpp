// Fill out your copyright notice in the Description page of Project Settings.

#include "GA_TargetActor_GetAround.h"
#include "GameplayAbility.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"


void AGA_TargetActor_GetAround::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());

}

void AGA_TargetActor_GetAround::ConfirmTargetingAndContinue()
{
	APawn* OwningPawn = MasterPC->GetPawn();

	if (!OwningPawn) {
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
		return;
	}
	FVector ViewPoint = OwningPawn->GetActorLocation();
	TArray<FOverlapResult> Overlaps;
	TArray < TWeakObjectPtr<AActor>> OverlapingActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn) {
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps,
		ViewPoint,
		FQuat::Identity,
		FCollisionObjectQueryParams(ECC_Pawn),
		FCollisionShape::MakeSphere(Radius),
		QueryParams);
	if (TryOverlap)
	{
		for (int i = 0; i < Overlaps.Num(); ++i)
		{
			APawn* PawnOverlaped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverlaped && !OverlapingActors.Contains(PawnOverlaped))
			{

				OverlapingActors.Add(PawnOverlaped);
			}

		}
	}
	if (OverlapingActors.Num() > 0)
	{	//UE_LOG(LogTemp, Warning, TEXT("ADD"));
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapingActors);
		
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else {
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}
