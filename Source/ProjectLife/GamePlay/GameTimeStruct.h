// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameTimeStruct.Generated.h"

USTRUCT(BlueprintType)
struct FGameTime
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

	/*Do Not Motify These Carelessly*/
	int32 MAXYEAR = 10000000;
	int32 MINYEAR = 0;

	int32 MAXMONTH = 12;
	int32 MINMONTH = 1;

	int32 MAXDAY = 28;
	int32 MINDAY = 1;

	int32 MAXHOUR = 24;
	int32 MINHOUR = 0;

	int32 MAXMINUTE = 60;
	int32 MINMINUTE = 0;
	/*END*/


	FGameTime(int32 InYear = 0, int32 InMonth = 1, int32 InDay = 1, int32 InHour = 0, int32 InMinute = 0);

	FGameTime operator+(const FGameTime& rValue);

	FString ToString();

};

USTRUCT(BlueprintType)
struct FMonthRow : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString MonthTitle;
};