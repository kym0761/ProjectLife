// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonTrigger.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PuzzleInterfaces.h"

AButtonTrigger::AButtonTrigger()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(40.0f);
	SetRootComponent(Sphere);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetCollisionProfileName(TEXT("NoCollision"));
	Body->SetupAttachment(RootComponent);

	Button = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button"));
	Button->SetCollisionProfileName(TEXT("NoCollision"));
	Button->SetupAttachment(Body);
}

void AButtonTrigger::BeginPlay()
{
	Super::BeginPlay();

	InitializeForTimeline();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AButtonTrigger::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AButtonTrigger::OnButtonEndOverlap);
}

void AButtonTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineHandle.TickTimeline(DeltaTime);

	//while Button Pressed Continuously, call Trigger()
	if (bTriggerActive)
	{
		Trigger();
	}

}

void AButtonTrigger::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UCharacterMovementComponent* characterMovement = OtherActor->FindComponentByClass<UCharacterMovementComponent>();
	UPrimitiveComponent* primitiveComp = OtherComp;

	//check if there is CharacterMovement or PhysicsComponent.
	if ((IsValid(characterMovement) || (primitiveComp && primitiveComp->IsSimulatingPhysics())) && bTriggerActive == false)
	{
		//Button Down.
		ButtonDown();
	}
}

void AButtonTrigger::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

		if (IsValid(characterMovement) || (IsValid(i) && i->IsSimulatingPhysics()))
		{
			temp = true;
			break;
		}
	}

	//Set bTriggerActivate with result.
	bTriggerActive = temp;

	//there is no Overlap, Button UP.
	if (bTriggerActive == false)
	{
		ButtonUp();
	}
}

void AButtonTrigger::InitializeForTimeline()
{
	if (CurveForTimeline)
	{
		FOnTimelineFloat timelineFloat;
		timelineFloat.BindDynamic(this, &AButtonTrigger::TimelineFloatFunction);

		TimelineHandle.AddInterpFloat(CurveForTimeline, timelineFloat);
		TimelineHandle.SetLooping(false);
	}
}

void AButtonTrigger::TimelineFloatFunction(float Value)
{
	FVector buttonRelativeLocation = FVector(0.0f,0.0f, Value);
	Button->SetRelativeLocation(buttonRelativeLocation);
}

void AButtonTrigger::ButtonUp()
{
	bTriggerActive = false;
	ButtonMeshUp();
	Trigger();
}

void AButtonTrigger::ButtonDown()
{
	bTriggerActive = true;
	ButtonMeshDown();
	Trigger();
}

void AButtonTrigger::ButtonMeshUp()
{
	TimelineHandle.Reverse();
}

void AButtonTrigger::ButtonMeshDown()
{
	TimelineHandle.Play();
}

void AButtonTrigger::Trigger()
{
	for (AActor* i : TriggeringArray)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UTriggerable::StaticClass());
		if (bInterfaceValid)
		{
			ITriggerable::Execute_TriggerAction(i);
		}
	}
}
