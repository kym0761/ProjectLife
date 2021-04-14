// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "../Farming/Crop.h"
#include "../Farming/GrowthComponent.h"

/*FGameTimeFunction*/

FGameTime::FGameTime()
{
	Hour = 0;
	Minute = 0;
}

FGameTime::FGameTime(int32 InHour, int32 InMinute)
{
	Hour = InHour;
	Minute = InMinute;
}

FGameTime FGameTime::operator+(const FGameTime& rValue)
{
	return FGameTime(Hour + rValue.Hour, Minute + rValue.Minute);
}

FString FGameTime::ToString()
{
	return FString::Printf(TEXT("Hour : %d -- Minute : %d"), Hour, Minute);
}

//FGameTime FGameTime::Plus_GameTime(FGameTime lValue, FGameTime rValue)
//{
//	return lValue + rValue;
//}

/*FGameTimeFunction End.*/

ABasicGameMode::ABasicGameMode()
{
	Day = 0;
	CurrentTime.Hour = 0;
	CurrentTime.Minute = 0;
}

void ABasicGameMode::IncreaseDay(int32 IncDay)
{
	Day += IncDay;
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
