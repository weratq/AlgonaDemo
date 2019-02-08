// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameplayEffectBase.h"

float UMyGameplayEffectBase::GetDuration()
{
	float MyDuration;
	if (DurationMagnitude.GetStaticMagnitudeIfPossible(1.f, MyDuration, nullptr))
	{
		return MyDuration;
	}
	return 0.0f;
}
