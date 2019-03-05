// Fill out your copyright notice in the Description page of Project Settings.

#include "AIGroundAbilityTargetActor.h"
#include "GameplayAbility.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"



AAIGroundAbilityTargetActor::AAIGroundAbilityTargetActor()
{
	Decal = CreateDefaultSubobject<UDecalComponent>("GroundDecal");
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	Decal->SetupAttachment(Root);
	Radius = 200.f;
	Decal->DecalSize = FVector(Radius);
}



void AAIGroundAbilityTargetActor::ConfirmTargetingAndContinue()
{
	

	TArray<FOverlapResult> Overlaps;
	TArray < TWeakObjectPtr<AActor>> OverlapingActors;

	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = false;
	QueryParams.bReturnPhysicalMaterial = false;
	
	if (ActorToIgnore) {
		QueryParams.AddIgnoredActor(ActorToIgnore);
	}

	bool TryOverlap = GetWorld()->OverlapMultiByObjectType(Overlaps,
		GetActorLocation(),
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

	FGameplayAbilityTargetData_LocationInfo* CenterLocation = new FGameplayAbilityTargetData_LocationInfo();
	if (Decal)
	{
		CenterLocation->TargetLocation.LiteralTransform = Decal->GetComponentTransform();
		CenterLocation->TargetLocation.LocationType = EGameplayAbilityTargetingLocationType::LiteralTransform;
	}

	if (OverlapingActors.Num() > 0)
	{	//UE_LOG(LogTemp, Warning, TEXT("ADD"));
		FGameplayAbilityTargetDataHandle TargetData = StartLocation.MakeTargetDataHandleFromActors(OverlapingActors);
		TargetData.Add(CenterLocation);
		TargetDataReadyDelegate.Broadcast(TargetData);
	}
	else {
		TargetDataReadyDelegate.Broadcast(FGameplayAbilityTargetDataHandle(CenterLocation));
	}
}
