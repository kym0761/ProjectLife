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
	for (AActor* i : ToTrigger)
	{
		if (!IsValid(i))
		{
			if (GEngine)
			{
				FString temp = FString("there is Not valid [ToTrigger] in : ") + GetName();
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Cyan, temp);
			}
			break;
		}


		//TriggerArray에 등록되어야 Trigger가 제대로 동작함.
		bool bIsChildOfPuzzleTrigger = i->GetClass()->IsChildOf(APuzzleTrigger::StaticClass());
		if (bIsChildOfPuzzleTrigger)
		{
			APuzzleTrigger* trigger = Cast<APuzzleTrigger>(i);
			if (trigger)
			{
				trigger->FromTrigger.Add(this);
			}
		}
	}
}
