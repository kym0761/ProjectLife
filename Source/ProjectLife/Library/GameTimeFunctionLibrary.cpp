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
