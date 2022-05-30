// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PuzzleTrigger.h"
#include "Components/WidgetComponent.h"
#include "DoorTimerWidget.h"
#include "FireStand.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APuzzleDoor::APuzzleDoor()
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
	bBoxOverlapping = false;
}

// Called when the game starts or when spawned
void APuzzleDoor::BeginPlay()
{
	//APuzzleDoor는 InitializeTriggerArray()을 Call할 필요가 없음.
	//APuzzleDoor가 누군가를 Trigger할 일은 지금 현재로는 없음.
	Super::Super::BeginPlay();
	
	//Set Default Widget Object.
	if (IsValid(Widget))
	{
		UDoorTimerWidget* timerWidget = Cast<UDoorTimerWidget>(Widget->GetUserWidgetObject());
		if (timerWidget)
		{
			timerWidget->DoorRef = this;
		}
	}

	//Init for Door Mesh Up And Down.
	InitializeForTimeline();

	Box->OnComponentBeginOverlap.AddDynamic(this, &APuzzleDoor::OnBoxBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &APuzzleDoor::OnBoxEndOverlap);

}

// Called every frame
void APuzzleDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Timeline Need this.
	TimelineHandle.TickTimeline(DeltaTime);

	//If there is CountDown.. Use This Function.
	if (bDoorOpen && bUseTimer)
	{
		CurrentTime = FMath::Clamp<float>(CurrentTime - DeltaTime, 0.0f, TriggerWaitTime);
		
		if (CurrentTime <= 0.0f && bBoxOverlapping == false)
		{
			CloseDoor();
		}
	}

}

void APuzzleDoor::TriggerAction_Implementation()
{

	bool bReady = true;

	//Check All Allocated Triggers are Being Activated.
	for (APuzzleTrigger* i : FromTrigger)
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

void APuzzleDoor::InitializeForTimeline()
{
	if (CurveForTimeline)
	{
		FOnTimelineFloat timelineFloat;
		timelineFloat.BindDynamic(this, &APuzzleDoor::TimelineFloatFunction);

		TimelineHandle.AddInterpFloat(CurveForTimeline, timelineFloat);
		TimelineHandle.SetLooping(false);
	}
}

void APuzzleDoor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCharacterMovementComponent* characterMovement = OtherActor->FindComponentByClass<UCharacterMovementComponent>();

	if ( IsValid(characterMovement) || (IsValid(OtherComp) && OtherComp->IsSimulatingPhysics()) )
	{
		bBoxOverlapping = true;
	}
}

void APuzzleDoor::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//Check Something Overlapping.
	TArray<UPrimitiveComponent*> overlappingComponents;
	GetOverlappingComponents(overlappingComponents);

	//temporary "false" Setting.
	bool temp = false;

	//check if there is CharacterMovement or PhysicsComponent.
	for (UPrimitiveComponent* i : overlappingComponents)
	{
		AActor* owner = i->GetOwner();
		UCharacterMovementComponent* characterMovement = owner->FindComponentByClass<UCharacterMovementComponent>();

		if (IsValid(characterMovement) || (IsValid(i) && i->IsSimulatingPhysics()) )
		{
			temp = true;
			break;
		}
	}

	//만약 아직 overlap하는 물체가 있다면 문 열린 상태를 그냥 유지함.
	//아니라면 false가 될 것이고 문이 닫힐 것임
	bBoxOverlapping = temp;

}

void APuzzleDoor::TimelineFloatFunction(float Value)
{
	FVector doorMeshLocation = FVector(0.0f,0.0f,Value);
	Mesh->SetRelativeLocation(doorMeshLocation);
}

void APuzzleDoor::OpenDoor()
{
	bDoorOpen = true;

	if (bUseTimer)
	{
		// If FireTorch is Using Timer, Then Set Time of This.
		bool bCheck = false;
		for (APuzzleTrigger* i : FromTrigger)
		{
			AFireStand* fireStand = Cast<AFireStand>(i);
			if (fireStand)
			{
				if (fireStand->bUseTimer)
				{
					bCheck = true;
					break;
				}
			}
		}

		//Refresh Time.
		if (bCheck)
		{
			float tempTime = 1000000.0f;

			//Get Remain Time which is Shortest.
			for (APuzzleTrigger* i : FromTrigger)
			{
				AFireStand* fireStand = Cast<AFireStand>(i);
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

void APuzzleDoor::CloseDoor()
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

void APuzzleDoor::Reset_Implementation()
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

