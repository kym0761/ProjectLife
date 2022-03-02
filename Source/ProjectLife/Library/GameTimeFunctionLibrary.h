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
		static FInGameTime Plus_GameTimeGameTime(FInGameTime InValue1, FInGameTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (GameTime)", CompactNodeTitle = "->", BlueprintAutocast), Category = "GameTime|Convert")
		static FString Conv_GameTimeToString(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetYear_GameTime(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetMonth_GameTime(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetDay_GameTime(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetHour_GameTime(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static int32 GetMinute_GameTime(FInGameTime InGameTime);

	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FInGameTime GetMorning_GameTime();
	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FInGameTime GetNoon_GameTime();
	UFUNCTION(BlueprintPure, Category = "GameTime|Get")
		static FInGameTime GetEvening_GameTime();
};
