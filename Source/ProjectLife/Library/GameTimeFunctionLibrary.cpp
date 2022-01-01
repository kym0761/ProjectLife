// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeFunctionLibrary.h"

FGameTime UGameTimeFunctionLibrary::Plus_GameTimeGameTime(FGameTime InValue1, FGameTime InValue2)
{
	return InValue1 + InValue2;
}

FString UGameTimeFunctionLibrary::Conv_GameTimeToString(FGameTime InGameTime)
{
	return InGameTime.ToString();
}

int32 UGameTimeFunctionLibrary::GetYear_GameTime(FGameTime InGameTime)
{
	return InGameTime.Year;
}

int32 UGameTimeFunctionLibrary::GetMonth_GameTime(FGameTime InGameTime)
{
	return InGameTime.Month;
}

int32 UGameTimeFunctionLibrary::GetDay_GameTime(FGameTime InGameTime)
{
	return InGameTime.Day;
}

int32 UGameTimeFunctionLibrary::GetHour_GameTime(FGameTime InGameTime)
{
	return InGameTime.Hour;
}

int32 UGameTimeFunctionLibrary::GetMinute_GameTime(FGameTime InGameTime)
{
	return InGameTime.Minute;
}
