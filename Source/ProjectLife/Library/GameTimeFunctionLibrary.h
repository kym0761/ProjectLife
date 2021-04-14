// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "../GamePlay/BasicGameMode.h"
#include "GameTimeFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UGameTimeFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public: // if this is a problem. just make it for only Conv_ Function.

	UFUNCTION(BlueprintPure, meta = (DisplayName = "GameTime + GameTime", CompactNodeTitle = "+", KeyWords = "+ Plus", CommutativeAssosiativeBinaryOperator = "true"))
		static FGameTime Plus_GameTimeGameTime(FGameTime InValue1, FGameTime InValue2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "ToString (GameTime)", CompactNodeTitle = "->", BlueprintAutocast),Category = "GameTime|Convert")
		static FString Conv_GameTimeToString(FGameTime InGameTime);
};
