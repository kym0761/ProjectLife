// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetButtonTriggerBase.h"
#include "PuzzleInterfaces.h"

void AResetButtonTriggerBase::BeginPlay()
{
	//Don't Call APuzzleTriggerBase's BeginPlay(). Only AActor's BeginPlay() is Called.
	//Because APuzzleTriggerBase's BeginPlay() Has Function that would Add [ResetButton] to TriggerArray.
	//if Do That, TriggerAction Not Functuate Unless Reset Button Pressed.
	//But, ResetButton Won't Be in Other's TriggerArray.
	Super::Super::Super::BeginPlay();

	InitializeForTimeline();

}

void AResetButtonTriggerBase::Tick(float DeltaTime)
{
	//ButtonTriggerBase Has Trigger() by Tick. So, Reset Button Don't Need to Reset Button.
	//Call AActor's Tick();
	Super::Super::Super::Tick(DeltaTime);

	TimelineHandle.TickTimeline(DeltaTime);
}

void AResetButtonTriggerBase::ButtonUp()
{
	//Base Button Trigger's ButtonUp() has "Trigger()" Function. Reset Don't need it. so, Override And Delete That Function.

	bTriggerActive = false;
	ButtonMeshUp();
}

void AResetButtonTriggerBase::Trigger()
{
	//find Resetable Actor and Do Reset.
	for (AActor* i : TriggeringArray)
	{
		bool bInterfaceValid = i->GetClass()->ImplementsInterface(UResetable::StaticClass());
		if (bInterfaceValid)
		{
			IResetable::Execute_Reset(i);
		}
	}
}