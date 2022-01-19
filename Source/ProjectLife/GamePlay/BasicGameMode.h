// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameTimeStruct.h"
#include "BasicGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API ABasicGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	ABasicGameMode();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

public:
	//increase Game's Day.
	UFUNCTION(BlueprintCallable)
		void IncreaseDay(int32 IncDay = 1);

	//Increase All Crop's Growth.
	void IncreaseGrowth(int32 IncGrowth = 1);
};
