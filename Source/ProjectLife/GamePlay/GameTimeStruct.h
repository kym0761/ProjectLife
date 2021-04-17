// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameTimeStruct.Generated.h"

USTRUCT(BlueprintType)
struct FGameTime
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Minute;

	//FGameTime();
	FGameTime(int32 InDay = 0, int32 InHour = 0, int32 InMinute = 0);

	FGameTime operator+(const FGameTime& rValue);

	FString ToString();

};