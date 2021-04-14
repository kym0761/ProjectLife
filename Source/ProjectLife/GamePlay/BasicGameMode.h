// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BasicGameMode.generated.h"


USTRUCT(BlueprintType)
struct FGameTime
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Hour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Minute;

	FGameTime();
	FGameTime(int32 InHour, int32 InMinute);

	FGameTime operator+(const FGameTime& rValue);

	FString ToString();
	//UFUNCTION(BlueprintCallable)
	//	FGameTime Plus_GameTime(FGameTime lValue, FGameTime rValue);
};

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ABasicGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ABasicGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
		FGameTime CurrentTime;

	UFUNCTION(BlueprintCallable)
		void IncreaseDay(int32 IncDay = 1);

	void IncreaseGrowth(int32 IncGrowth = 1);
};
