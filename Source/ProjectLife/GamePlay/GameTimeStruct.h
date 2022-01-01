// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTimeStruct.Generated.h"

USTRUCT(BlueprintType)
struct FGameTime
{
	GENERATED_BODY()

public:

	int32 MAXYEAR = 10000000;
	int32 MAXMONTH = 12;
	int32 MAXDAY = 28;
	int32 MAXHOUR = 24;
	int32 MAXMINUTE = 60;

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

	//FGameTime();
	FGameTime(int32 InYear = 0, int32 InMonth = 0, int32 InDay = 0, int32 InHour = 0, int32 InMinute = 0);

	FGameTime operator+(const FGameTime& rValue);

	FString ToString();

};