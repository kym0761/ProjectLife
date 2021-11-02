// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStruct.h"

FAbilityDataStruct::FAbilityDataStruct()
{
	Duration = 5.0f;
	Cooldown = 5.0f;
	AbilityEffectAmount = 20.0f;
	AbilityType = EAbilityType::None;
	bIsInifinity = false;
	CastingTime = 2.0f;
	Thumbnail = nullptr;
}
