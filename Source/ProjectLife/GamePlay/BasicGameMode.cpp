// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Farming/Crop.h"
#include "../Farming/GrowthComponent.h"
#include "../ProjectLIfeGameInstance.h"
#include "../Inventory/InventoryManager.h"

ABasicGameMode::ABasicGameMode()
{

}

void ABasicGameMode::IncreaseDay(int32 IncDay)
{
	UProjectLIfeGameInstance * gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

	if (IsValid(gameInstance))
	{
		FGameTime currentGameTime = gameInstance->GameTime;

		FGameTime tomorrow(0, 0, 0, 0, 0);
		tomorrow.Year = currentGameTime.Year;
		tomorrow.Month = currentGameTime.Month;
		tomorrow.Day = currentGameTime.Day;

		if (currentGameTime.Hour >= FGameTime::Morning().Hour) // still Today.
		{
			tomorrow += FGameTime(0, 0, IncDay, 0, 0) + FGameTime::Morning();
		}
		else // already tomorrow
		{
			tomorrow += FGameTime::Morning();
		}

		gameInstance->GameTime = tomorrow;

		IncreaseGrowth();
	}

}

void ABasicGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void ABasicGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetWorld()->SpawnActor<AInventoryManager>(AInventoryManager::StaticClass(),FTransform::FTransform());
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
