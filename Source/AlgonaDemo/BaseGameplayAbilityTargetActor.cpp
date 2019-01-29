// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameplayAbilityTargetActor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"



void ABaseGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorInfo()->GetInstigatorController());
}

void ABaseGameplayAbilityTargetActor::ConfirmTargetingAndContinue()
{
	FVector ViewPoint;
	GetPlayerLookingPoint(ViewPoint);

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
		for (int32 i; i < Overlaps.Num(); ++i)
		{
			APawn* PawnOverlaped = Cast<APawn>(Overlaps[i].GetActor());
			if (PawnOverlaped && !OverlapingActors.Contains(PawnOverlaped))
			{
				OverlapingActors.Add(PawnOverlaped);
			}

		}
	}

}

bool ABaseGameplayAbilityTargetActor::GetPlayerLookingPoint(OUT FVector& OutViewPoint)
{
	FVector ViewPoint;
	FRotator ViewRatation;
	MasterPC->GetPlayerViewPoint(ViewPoint, ViewRatation);
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	APawn* MasterPawn = MasterPC->GetPawn();
	if (MasterPawn) {
		QueryParams.AddIgnoredActor(MasterPawn->GetUniqueID());
	}

	
	bool TryTrace = GetWorld()->LineTraceSingleByChannel(HitResult,
		ViewPoint,
		ViewPoint + ViewRatation.Vector() * 1000.f, ECC_Visibility,
		QueryParams,
		FCollisionResponseParams::DefaultResponseParam);

	if (TryTrace) {
		OutViewPoint = HitResult.ImpactPoint;
	}
	else {
		OutViewPoint = FVector();
	}
	return TryTrace;
}
