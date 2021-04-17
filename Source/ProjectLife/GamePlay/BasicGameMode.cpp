// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Farming/Crop.h"
#include "../Farming/GrowthComponent.h"


ABasicGameMode::ABasicGameMode()
{
	CurrentGameTime.Hour = 0;
	CurrentGameTime.Minute = 0;
}

void ABasicGameMode::IncreaseDay(int32 IncDay)
{
	CurrentGameTime.Day += IncDay;

	IncreaseGrowth();
}

void ABasicGameMode::IncreaseGrowth(int32 IncGrowth)
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
