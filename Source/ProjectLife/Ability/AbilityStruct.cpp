// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStruct.h"

FAbilityDataStruct::FAbilityDataStruct()
{
	Thumbnail = nullptr;

	AbilityDurabilityType = EAbilityDurabilityType::Limited;
	Duration = 5.0f;
	Cooldown = 5.0f;
	
	AbilityType = EAbilityType::None;
	
	AbilityEffectAmount1 = 20.0f;
	AbilityEffectAmount2 = 00.0f;
	AbilityEffectAmount3 = 00.0f;
	
	AbilityCoefficientAmount1 = 0.0f;
	AbilityCoefficientAmount2 = 0.0f;
	AbilityCoefficientAmount3 = 0.0f;

	CastingTime = 2.0f;
}
