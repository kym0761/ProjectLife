// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTrigger.h"
#include "PuzzleDoor.h"

// Sets default values
APuzzleTrigger::APuzzleTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bTriggerActive = false;
}

// Called when the game starts or when spawned
void APuzzleTrigger::BeginPlay()
{
	Super::BeginPlay();

	InitializeTriggerArray();
}

// Called every frame
void APuzzleTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleTrigger::InitializeTriggerArray()
{
	for (auto i : TriggeringArray)
	{
		if (!IsValid(i))
		{
			if (GEngine)
			{
				FString temp = FString("there is Not valid [TriggeringArray] in : ") + GetName();
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Cyan, temp);
			}
			break;
		}

		bool bIsChildOfPuzzleTrigger = i->GetClass()->IsChildOf(APuzzleTrigger::StaticClass());
		if (bIsChildOfPuzzleTrigger)
		{
			APuzzleTrigger* trigger = Cast<APuzzleTrigger>(i);
			if (trigger)
			{
				trigger->TriggerArray.Add(this);
			}
		}
		else
		{
			bool bIsChildOfPuzzleDoor = i->GetClass()->IsChildOf(APuzzleDoor::StaticClass());
			if (bIsChildOfPuzzleDoor)
			{
				APuzzleDoor* door = Cast<APuzzleDoor>(i);
				if (door)
				{
					door->TriggerArray.Add(this);
				}
			}
		}
	}
}
