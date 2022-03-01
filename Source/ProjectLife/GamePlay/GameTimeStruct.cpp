// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeStruct.h"

FInGameTime::FInGameTime(int32 InYear, int32 InMonth, int32 InDay, int32 InHour, int32 InMinute)
{
	Year = FMath::Clamp(InYear, 0, MAXYEAR);
	Month = FMath::Clamp(InMonth, 0, MAXMONTH);
	Day = FMath::Clamp(InDay, 0, MAXDAY);
	Hour = FMath::Clamp(InHour, 0, MAXHOUR - 1);
	Minute = FMath::Clamp(InMinute, 0, MAXMINUTE - 1);
}

FInGameTime FInGameTime::operator+(const FInGameTime& rValue)
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

	return FInGameTime(year, month, day, hour, minute);
}

FInGameTime& FInGameTime::operator+=(const FInGameTime& rValue)
{
	*this = *this + rValue;

	return *this;
}

FInGameTime FInGameTime::operator-(const FInGameTime& rValue)
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


	return FInGameTime(year, month, day, hour, minute);
}

FInGameTime& FInGameTime::operator-=(const FInGameTime& rValue)
{
	*this = *this - rValue;

	return *this;
}

FString FInGameTime::ToString()
{
	return FString::Printf(TEXT("| Year : %d -- Month : %d -- Day : %d -- Hour : %d -- Minute : %d |"), Year, Month, Day, Hour, Minute);
}

FInGameTime FInGameTime::Morning()
{
	return FInGameTime(0, 0, 0, 6, 0);
}

FInGameTime FInGameTime::Noon()
{
	return FInGameTime(0, 0, 0, 12, 0);
}

FInGameTime FInGameTime::Evening()
{
	return FInGameTime(0, 0, 0, 18, 0);
}
