// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonTriggerBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PuzzleInterfaces.h"

AButtonTriggerBase::AButtonTriggerBase()
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

void AButtonTriggerBase::BeginPlay()
{
	Super::BeginPlay();

	InitializeForTimeline();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AButtonTriggerBase::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AButtonTriggerBase::OnButtonEndOverlap);
}

void AButtonTriggerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineHandle.TickTimeline(DeltaTime);

	//while Button Pressed Continuously, call Trigger()
	if (bTriggerActive)
	{
		Trigger();
	}

}

void AButtonTriggerBase::OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

void AButtonTriggerBase::OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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

void AButtonTriggerBase::InitializeForTimeline()
{
	if (CurveForTimeline)
	{
		FOnTimelineFloat timelineFloat;
		timelineFloat.BindDynamic(this, &AButtonTriggerBase::TimelineFloatFunction);

		TimelineHandle.AddInterpFloat(CurveForTimeline, timelineFloat);
		TimelineHandle.SetLooping(false);
	}
}

void AButtonTriggerBase::TimelineFloatFunction(float Value)
{
	FVector buttonRelativeLocation = FVector(0.0f,0.0f, Value);
	Button->SetRelativeLocation(buttonRelativeLocation);
}

void AButtonTriggerBase::ButtonUp()
{
	bTriggerActive = false;
	ButtonMeshUp();
	Trigger();
}

void AButtonTriggerBase::ButtonDown()
{
	bTriggerActive = true;
	ButtonMeshDown();
	Trigger();
}

void AButtonTriggerBase::ButtonMeshUp()
{
	TimelineHandle.Reverse();
}

void AButtonTriggerBase::ButtonMeshDown()
{
	TimelineHandle.Play();
}

void AButtonTriggerBase::Trigger()
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
