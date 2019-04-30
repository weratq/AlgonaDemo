// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseGameplayAbility.h"

FGameplayAbilityInfo UBaseGameplayAbility::GetAbilityInfo()
{
	UGameplayEffect* CoolDownEffect = GetCooldownGameplayEffect();
	UGameplayEffect* CostEffect = GetCostGameplayEffect();
	if (CoolDownEffect && CostEffect) {
		float CoolDownDuration = 0.f;
		CoolDownEffect->DurationMagnitude.GetStaticMagnitudeIfPossible(1, CoolDownDuration);
		float Cost = 0.f;
		EAbilityCostType CostType;
		TArray<F_GA_LevelEffects> LE_InfoList;

		if (CostEffect->Modifiers.Num() > 0) {
			FGameplayModifierInfo EffectInfo = CostEffect->Modifiers[0];
			EffectInfo.ModifierMagnitude.GetStaticMagnitudeIfPossible(1, Cost);
			FGameplayAttribute CostAttr = EffectInfo.Attribute;
			FString AttributeName = CostAttr.AttributeName;
			if (AttributeName == "Health") { CostType = EAbilityCostType::Health; }
			else if(AttributeName == "Mana") { CostType = EAbilityCostType::Mana; }
			else if (AttributeName == "Strength") { CostType = EAbilityCostType::Strength;}
		}
		if (LevelEffectList.IsValidIndex(0))
		{
			for (int i = 0; i < LevelEffectList.Num(); ++i)
			{
				LE_InfoList.Add(LevelEffectList[i].GetEffectInfo(LevelEffectList[i]));
			}
		}

		return FGameplayAbilityInfo(CoolDownDuration,Cost,CostType,UIMaterial,GetClass(),LE_InfoList);
	}
	return FGameplayAbilityInfo();
	
}

F_GA_LevelEffects F_GA_LevelEffectList::GetEffectInfo(F_GA_LevelEffectList Effect)
{
	UDotGameplayEffectUIData* MyUIData;
	MyUIData = Cast<UDotGameplayEffectUIData>(Effect.GamePlayEffect.GetDefaultObject()->UIData);
	if (MyUIData!=nullptr)
	{
		F_GA_LevelEffects Final;
		Final.LevelToUnlock = Effect.NeedLevel;
		Final.Icon = MyUIData->IconMaterial;
		Final.Description = MyUIData->Description;
		return Final;
	}
	return F_GA_LevelEffects();
}
