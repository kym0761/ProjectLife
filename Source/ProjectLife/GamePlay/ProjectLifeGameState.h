// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameTimeStruct.h"
#include "ProjectLifeGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AProjectLifeGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	AProjectLifeGameState();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "InGameTime")
		FInGameTime InGameTime;

};
