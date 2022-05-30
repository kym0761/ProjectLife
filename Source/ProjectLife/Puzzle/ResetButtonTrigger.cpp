// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetButtonTrigger.h"
#include "PuzzleInterfaces.h"
#include "Components/SphereComponent.h"

AResetButtonTrigger::AResetButtonTrigger()
{

}

void AResetButtonTrigger::BeginPlay()
{
	//Don't Call APuzzleTrigger's BeginPlay(). Only AActor's BeginPlay() is Called.
	//Because APuzzleTrigger's BeginPlay() Has Function that would Add [ResetButton] to TriggerArray.
	//if Do That, TriggerAction Not Functuate Unless Reset Button Pressed.
	//But, ResetButton Won't Be in Other's TriggerArray.
	Super::Super::Super::BeginPlay();

	InitializeForTimeline();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AResetButtonTrigger::OnButtonBeginOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AResetButtonTrigger::OnButtonEndOverlap);
}

void AResetButtonTrigger::Tick(float DeltaTime)
{
	//ButtonTrigger Has Trigger() by Tick. So, Reset Button Don't Need to Reset Button.
	//Call AActor's Tick();
	Super::Super::Super::Tick(DeltaTime);

	TimelineHandle.TickTimeline(DeltaTime);
}

void AResetButtonTrigger::ButtonUp()
{
	// Button Trigger's ButtonUp() has "Trigger()" Function. Reset Don't need it. so, Override And Delete That Function.

	bTriggerActive = false;
	ButtonMeshUp();
}

void AResetButtonTrigger::Trigger()
{
	//find Resetable Actor and Do Reset.
	for (AActor* i : ToTrigger)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UResetable::StaticClass());
		if (bInterfaceValid)
		{
			IResetable::Execute_Reset(i);
		}
	}
}