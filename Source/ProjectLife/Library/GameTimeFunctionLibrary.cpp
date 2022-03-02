// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeFunctionLibrary.h"

FInGameTime UGameTimeFunctionLibrary::Plus_GameTimeGameTime(FInGameTime InValue1, FInGameTime InValue2)
{
	return InValue1 + InValue2;
}

FString UGameTimeFunctionLibrary::Conv_GameTimeToString(FInGameTime InGameTime)
{
	return InGameTime.ToString();
}

int32 UGameTimeFunctionLibrary::GetYear_GameTime(FInGameTime InGameTime)
{
	return InGameTime.Year;
}

int32 UGameTimeFunctionLibrary::GetMonth_GameTime(FInGameTime InGameTime)
{
	return InGameTime.Month;
}

int32 UGameTimeFunctionLibrary::GetDay_GameTime(FInGameTime InGameTime)
{
	return InGameTime.Day;
}

int32 UGameTimeFunctionLibrary::GetHour_GameTime(FInGameTime InGameTime)
{
	return InGameTime.Hour;
}

int32 UGameTimeFunctionLibrary::GetMinute_GameTime(FInGameTime InGameTime)
{
	return InGameTime.Minute;
}

FInGameTime UGameTimeFunctionLibrary::GetMorning_GameTime()
{
	return FInGameTime::Morning();
}

FInGameTime UGameTimeFunctionLibrary::GetNoon_GameTime()
{
	return FInGameTime::Noon();
}

FInGameTime UGameTimeFunctionLibrary::GetEvening_GameTime()
{
	return FInGameTime::Evening();
}
