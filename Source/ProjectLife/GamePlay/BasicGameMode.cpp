// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Farming/Crop.h"
#include "../Farming/GrowthComponent.h"
#include "../ProjectLIfeGameInstance.h"

ABasicGameMode::ABasicGameMode()
{

}

void ABasicGameMode::IncreaseDay(int32 IncDay)
{
	UProjectLIfeGameInstance * gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

	if (IsValid(gameInstance))
	{
		gameInstance->GameTime = gameInstance->GameTime + FGameTime(0, 0, IncDay, 0, 0);

		IncreaseGrowth();
	}
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
