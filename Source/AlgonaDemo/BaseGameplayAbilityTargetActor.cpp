// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameplayAbilityTargetActor.h"
#include "GameFramework/PlayerController.h"
#include "GameplayAbility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ABaseGameplayAbilityTargetActor::ABaseGameplayAbilityTargetActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Decal = CreateDefaultSubobject<UDecalComponent>("GroundDecal");
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Decal->SetupAttachment(Root);
	Radius = 200.f;
	Decal->DecalSize = FVector(Radius);
	
}

void ABaseGameplayAbilityTargetActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	FVector LookPoint;
	GetPlayerLookingPoint(LookPoint);
	Decal->SetWorldLocation(LookPoint, false, nullptr, ETeleportType::None);
	//DrawDebugSphere(GetWorld(), LookPoint, Radius, 32, FColor::Red, false, -1, 0, 5.f);
}



void ABaseGameplayAbilityTargetActor::StartTargeting(UGameplayAbility* Ability)
{
	OwningAbility = Ability;
	MasterPC = Cast<APlayerController>(Ability->GetOwningActorFromActorInfo()->GetInstigatorController());

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
	{	UE_LOG(LogTemp, Warning, TEXT("ADD"));
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapingActors);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else {
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle());
	}
}





bool ABaseGameplayAbilityTargetActor::GetPlayerLookingPoint(FVector& OutViewPoint)
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
