// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleTriggerBase.h"
#include "PuzzleDoorBase.h"

// Sets default values
APuzzleTriggerBase::APuzzleTriggerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bTriggerActive = false;
}

// Called when the game starts or when spawned
void APuzzleTriggerBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeTriggerArray();
}

// Called every frame
void APuzzleTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APuzzleTriggerBase::InitializeTriggerArray()
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

		bool bIsChildOfPuzzleTrigger = i->GetClass()->IsChildOf(APuzzleTriggerBase::StaticClass());
		if (bIsChildOfPuzzleTrigger)
		{
			APuzzleTriggerBase* trigger = Cast<APuzzleTriggerBase>(i);
			if (trigger)
			{
				trigger->TriggerArray.Add(this);
			}
		}
		else
		{
			bool bIsChildOfPuzzleDoor = i->GetClass()->IsChildOf(APuzzleDoorBase::StaticClass());
			if (bIsChildOfPuzzleDoor)
			{
				APuzzleDoorBase* door = Cast<APuzzleDoorBase>(i);
				if (door)
				{
					door->TriggerArray.Add(this);
				}
			}
		}
	}
}
