// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../GamePlay/GameTimeStruct.h"
#include "GameTimeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UGameTimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: // if this is a problem. just make sure it for only Conv_ Functions.

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime + GameTime", CompactNodeTitle = "+", KeyWords = "+ Plus", CommutativeAssosiativeBinaryOperator = "true"), Category = "GameTime|Convert")
		static FGameTime Plus_GameTimeGameTime(FGameTime InValue1, FGameTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (GameTime)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameTime|Convert")
		static FString Conv_GameTimeToString(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetYear_GameTime(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetMonth_GameTime(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetDay_GameTime(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetHour_GameTime(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetMinute_GameTime(FGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FGameTime GetMorning_GameTime();
	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FGameTime GetNoon_GameTime();
	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FGameTime GetEvening_GameTime();
};
