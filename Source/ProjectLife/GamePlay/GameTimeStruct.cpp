// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeStruct.h"

FGameTime::FGameTime(int32 InDay, int32 InHour, int32 InMinute)
{
	Day = InDay;
	Hour = FMath::Clamp(InHour, 0, 24);
	Minute = FMath::Clamp(InMinute, 0, 60);
}

FGameTime FGameTime::operator+(const FGameTime& rValue)
{
	//todo : Need To Clamp And Adjust Hour And Minute Calculation.

	return FGameTime(Day + rValue.Day, Hour + rValue.Hour, Minute + rValue.Minute);
}

FString FGameTime::ToString()
{
	return FString::Printf(TEXT("Day : %d -- Hour : %d -- Minute : %d"), Day, Hour, Minute);
}