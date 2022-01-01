// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeStruct.h"

FGameTime::FGameTime(int32 InYear, int32 InMonth, int32 InDay, int32 InHour, int32 InMinute)
{
	Year = FMath::Clamp(InYear, 0, MAXYEAR);
	Month = FMath::Clamp(InMonth, 1, MAXMONTH);
	Day = FMath::Clamp(InDay, 1, MAXDAY);
	Hour = FMath::Clamp(InHour, 0, MAXHOUR - 1);
	Minute = FMath::Clamp(InMinute, 0, MAXMINUTE - 1);
}

FGameTime FGameTime::operator+(const FGameTime& rValue)
{
	//todo : Need To Clamp And Adjust Hour And Minute Calculation.
	
	int32 year = this->Year + rValue.Year;
	int32 month = this->Month + rValue.Month;
	int32 day = this->Day + rValue.Day;
	int32 hour = this->Hour + rValue.Hour;
	int32 minute = this->Minute + rValue.Minute;

	if (minute >= MAXMINUTE)
	{
		minute = minute % MAXMINUTE;
		hour++;
	}

	if (hour >= MAXHOUR)
	{
		hour = hour % MAXHOUR;
		day++;
	}

	if (day > MAXDAY)
	{
		day = day % MAXDAY;
		month++;
	}
	
	if (month > MAXMONTH)
	{
		month = month % MAXMONTH;
		year++;
	}

	if (year > MAXYEAR)
	{
		year = FMath::Clamp(year, 0, MAXYEAR);
	}

	return FGameTime(year, month, day, hour, minute);
}

FString FGameTime::ToString()
{
	return FString::Printf(TEXT("Day : %d -- Hour : %d -- Minute : %d"), Day, Hour, Minute);
}