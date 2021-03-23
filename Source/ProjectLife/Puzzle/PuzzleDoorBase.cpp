// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDoorBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PuzzleTriggerBase.h"
#include "Components/WidgetComponent.h"
#include "DoorTimerWidgetBase.h"
#include "FireStandBase.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values
APuzzleDoorBase::APuzzleDoorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetVisibility(false);
	Widget->SetHiddenInGame(true);
	Widget->SetupAttachment(RootComponent);

	CurrentTime = 0.0f;
	TriggerWaitTime = 5.0f;

	bDoorOpen = false;
	bUseTimer = false;
	bOpenPermanently = false;
}

// Called when the game starts or when spawned
void APuzzleDoorBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Set Default Widget Object.
	if (IsValid(Widget))
	{
		UDoorTimerWidgetBase* timerWidget = Cast<UDoorTimerWidgetBase>(Widget->GetUserWidgetObject());
		if (timerWidget)
		{
			timerWidget->DoorRef = this;
		}
	}

	//Init for Door Mesh Up And Down.
	InitializeForTimeline();

}

// Called every frame
void APuzzleDoorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Timeline Need this.
	TimelineHandle.TickTimeline(DeltaTime);

	//If there is CountDown.. Use This Function.
	if (bDoorOpen && bUseTimer)
	{
		CurrentTime = FMath::Clamp<float>(CurrentTime - DeltaTime, 0.0f, TriggerWaitTime);
		
		if (CurrentTime <= 0.0f)
		{
			CloseDoor();
		}
	}

}

void APuzzleDoorBase::TriggerAction_Implementation()
{

	bool bReady = true;

	//Check All Allocated Triggers are Being Activated.
	for (APuzzleTriggerBase* i : TriggerArray)
	{
		//One Of Them is not Activated.
		if (i->bTriggerActive == false)
		{
			bReady = false;
			break;
		}
	}

	if (bReady)
	{
		OpenDoor();
	}
	else if(!bReady && !bUseTimer && !bOpenPermanently)
	{
		CloseDoor();
	}
}

void APuzzleDoorBase::InitializeForTimeline()
{
	if (CurveForTimeline)
	{
		FOnTimelineFloat timelineFloat;
		timelineFloat.BindDynamic(this, &APuzzleDoorBase::TimelineFloatFunction);

		TimelineHandle.AddInterpFloat(CurveForTimeline, timelineFloat);
		TimelineHandle.SetLooping(false);
	}
}

void APuzzleDoorBase::TimelineFloatFunction(float Value)
{
	FVector doorMeshLocation = FVector(0.0f,0.0f,Value);
	Mesh->SetRelativeLocation(doorMeshLocation);
}

void APuzzleDoorBase::OpenDoor()
{
	bDoorOpen = true;

	if (bUseTimer)
	{
		// If FireTorch is Using Timer, Then Set Time of This.
		bool bCheck = false;
		for (APuzzleTriggerBase* i : TriggerArray)
		{
			AFireStandBase* fireStand = Cast<AFireStandBase>(i);
			if (fireStand)
			{
				if (fireStand->bUseTimer)
				{
					bCheck = true;
					break;
				}
			}
		}

		if (bCheck)
		{
			float tempTime = 1000000.0f;

			for (APuzzleTriggerBase* i : TriggerArray)
			{
				AFireStandBase* fireStand = Cast<AFireStandBase>(i);
				if (fireStand)
				{
					if (fireStand->CurrentTime < tempTime)
					{
						tempTime = fireStand->CurrentTime;
					}
				}
			}

			CurrentTime = tempTime;
		}
		else
		{
			CurrentTime = TriggerWaitTime;
		}
		
		if (IsValid(Widget))
		{
			Widget->SetVisibility(true);
			Widget->SetHiddenInGame(false);
		}
	}

	TimelineHandle.Play();
}

void APuzzleDoorBase::CloseDoor()
{
	bDoorOpen = false;
	TimelineHandle.Reverse();

	if (bUseTimer)
	{
		if (IsValid(Widget))
		{
			Widget->SetVisibility(false);
			Widget->SetHiddenInGame(true);
		}
	}
}

void APuzzleDoorBase::Reset_Implementation()
{
	bDoorOpen = false;
	TimelineHandle.SetNewTime(0.0f);
	TimelineHandle.Stop();

	if (bUseTimer)
	{
		if (IsValid(Widget))
		{
			Widget->SetVisibility(false);
			Widget->SetHiddenInGame(true);
		}
	}

	if (ResetNiagaraSystem)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ResetNiagaraSystem,GetActorLocation());
	}

}

