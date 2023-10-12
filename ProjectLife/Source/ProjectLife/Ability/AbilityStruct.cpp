// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStruct.h"

FAbilityDataStruct::FAbilityDataStruct()
{
	Thumbnail = nullptr;

	AbilityDurabilityType = EAbilityDurabilityType::Limited;
	Duration = 5.0f;
	Cooldown = 5.0f;
	
	AbilityType = EAbilityType::None;

	AbilityEffectAmounts.Add(20.0f);
	AbilityCoefficientAmounts.Add(1.0f);

	CastingTime = 2.0f;
}
