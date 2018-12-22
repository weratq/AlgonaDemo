// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "MyStructureObject.h"
#include "Engine/Public/TimerManager.h"
#include "SkillEffectComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChangeDotArr);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALGONADEMO_API USkillEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	float Dot(float tick, float TimeRemaiting);
	UFUNCTION(BlueprintCallable)
	void ReturnDamage();

	UFUNCTION(BlueprintCallable)
	void AddDot( FDotTickEffect DotToAdd );
	UFUNCTION(BlueprintCallable)
	void RefreshDot(int IndexInDotOn);


	UPROPERTY(BlueprintAssignable)
		FChangeDotArr OnChangeDotArr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray <FDotTickEffect> DotOn;
};
