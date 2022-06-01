// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "GameTimeStruct.h"
#include "ProjectLifeGameState.generated.h"

/**
 * InGameTime처럼 게임에서 공용으로 쓰일 State를 여기에 지정할 것.
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
