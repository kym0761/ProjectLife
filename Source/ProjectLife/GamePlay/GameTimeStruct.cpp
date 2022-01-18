// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeStruct.h"

FGameTime::FGameTime(int32 InYear, int32 InMonth, int32 InDay, int32 InHour, int32 InMinute)
{
	Year = FMath::Clamp(InYear, 0, MAXYEAR);
	Month = FMath::Clamp(InMonth, 0, MAXMONTH);
	Day = FMath::Clamp(InDay, 0, MAXDAY);
	Hour = FMath::Clamp(InHour, 0, MAXHOUR - 1);
	Minute = FMath::Clamp(InMinute, 0, MAXMINUTE - 1);
}

FGameTime FGameTime::operator+(const FGameTime& rValue)
{
	int32 year = this->Year + rValue.Year;
	int32 month = this->Month + rValue.Month;
	int32 day = this->Day + rValue.Day;
	int32 hour = this->Hour + rValue.Hour;
	int32 minute = this->Minute + rValue.Minute;

	/*to Avoid Overflow or Unwanted Calculations.*/
	if (year < 0 || month < 0 || day < 0 || hour < 0 || minute < 0)
	{
		return *this;
	}

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

FGameTime& FGameTime::operator+=(const FGameTime& rValue)
{
	*this = *this + rValue;

	return *this;
}

FGameTime FGameTime::operator-(const FGameTime& rValue)
{
	int32 year = this->Year - rValue.Year;
	int32 month = this->Month - rValue.Month;
	int32 day = this->Day - rValue.Day;
	int32 hour = this->Hour - rValue.Hour;
	int32 minute = this->Minute - rValue.Minute;

	if (minute < 0)
	{
		minute = minute + MAXMINUTE;
		hour--;
	}

	if (hour < 0)
	{
		hour = hour + MAXHOUR;
		day--;
	}

	if (day <= 0)
	{
		day = day + MAXDAY;
		month--;
	}

	if (month <= 0)
	{
		month = month + MAXMONTH;
		year--;
	}


	return FGameTime(year, month, day, hour, minute);
}

FGameTime& FGameTime::operator-=(const FGameTime& rValue)
{
	*this = *this - rValue;

	return *this;
}

FString FGameTime::ToString()
{
	return FString::Printf(TEXT("| Year : %d -- Month : %d -- Day : %d -- Hour : %d -- Minute : %d |"), Year, Month, Day, Hour, Minute);
}

FGameTime FGameTime::Morning()
{
	return FGameTime(0, 0, 0, 6, 0);
}

FGameTime FGameTime::Noon()
{
	return FGameTime(0, 0, 0, 12, 0);
}

FGameTime FGameTime::Evening()
{
	return FGameTime(0, 0, 0, 18, 0);
}
