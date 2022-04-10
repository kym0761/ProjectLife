// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameTimeStruct.Generated.h"

USTRUCT(BlueprintType)
struct FInGameTime
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Year;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Month;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Minute;

#pragma region ConstTimeValue
	/*Do Not Motify These Carelessly*/
	static const int32 MAXYEAR = 10000000;
	static const int32 MAXMONTH = 12;
	static const int32 MAXDAY = 30;
	static const int32 MAXHOUR = 24;
	static const int32 MAXMINUTE = 60;
	static const int32 WEEK = 7;
	/*END*/
#pragma endregion

	FInGameTime(int32 InYear = 0, int32 InMonth = 1, int32 InDay = 1, int32 InHour = 0, int32 InMinute = 0);

	FInGameTime operator+(const FInGameTime& rValue);
	FInGameTime& operator+=(const FInGameTime& rValue);

	FInGameTime operator-(const FInGameTime& rValue);
	FInGameTime& operator-=(const FInGameTime& rValue);

	FString ToString();

	static FInGameTime Morning();
	static FInGameTime Noon();
	static FInGameTime Evening();
};

USTRUCT(BlueprintType)
struct FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MonthName;
};

USTRUCT(BlueprintType)
struct FSeasonRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SeasonName;
};