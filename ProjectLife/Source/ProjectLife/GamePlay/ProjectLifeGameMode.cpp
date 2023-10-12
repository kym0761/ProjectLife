// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLifeGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Farming/Crop.h"
#include "Farming/GrowthComponent.h"
#include "ProjectLifeGameState.h"

AProjectLifeGameMode::AProjectLifeGameMode()
{
}

void AProjectLifeGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectLifeGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AProjectLifeGameMode::IncreaseDay(int32 IncDay)
{
	AProjectLifeGameState* gameState = GetGameState<AProjectLifeGameState>();

	if (IsValid(gameState))
	{
		FInGameTime currentInGameTime = gameState->InGameTime;


		FInGameTime tomorrow(0, 0, 0, 0, 0);
		tomorrow.Year = currentInGameTime.Year;
		tomorrow.Month = currentInGameTime.Month;
		tomorrow.Day = currentInGameTime.Day;

		if (currentInGameTime.Hour >= FInGameTime::Morning().Hour) // still Today. EX) 17:00, 23:40...
		{
			tomorrow += FInGameTime(0, 0, IncDay, 0, 0) + FInGameTime::Morning();
		}
		else // already tomorrow EX) 0:40
		{
			tomorrow += FInGameTime::Morning();
		}

		gameState->InGameTime = tomorrow;

		IncreaseGrowth();
	}
}

void AProjectLifeGameMode::IncreaseGrowth(int32 IncGrowth)
{
	TArray<AActor*> hasGrowthArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACrop::StaticClass(), hasGrowthArray);

	for (AActor* i : hasGrowthArray)
	{
		UGrowthComponent* growthComponent = i->FindComponentByClass<UGrowthComponent>();
		if (growthComponent)
		{
			growthComponent->Grow();
		}
	}
}
