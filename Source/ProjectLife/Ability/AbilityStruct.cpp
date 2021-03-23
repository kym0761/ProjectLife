// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityStruct.h"

FBuffDataStruct::FBuffDataStruct()
{
	BuffDuration = 5.0f;
	Cooldown = 1.0f;
	BuffAmount = 0.25f;
	BuffType = EBuffType::None;
	Thumbnail = nullptr;
	CastingTime = 2.0f;
}

FDeBuffDataStruct::FDeBuffDataStruct()
{
	DeBuffDuration = 5.0f;
	Cooldown = 1.0f;
	DeBuffAmount = 0.25f;
	DeBuffType = EDeBuffType::None;
	Thumbnail = nullptr;
	CastingTime = 2.0f;
}
