// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTimerWidgetBase.h"
#include "Components/ProgressBar.h"
#include "PuzzleDoorBase.h"
void UDoorTimerWidgetBase::NativeConstruct()
{

	if (TimerProgressBar)
	{
		//TimerProgressBar->PercentDelegate.BindDynamic(this, &UDoorTimerWidgetBase::DoorPercent);
		TimerProgressBar->PercentDelegate.BindUFunction(this, TEXT("DoorPercent"));
		TimerProgressBar->SynchronizeProperties();
	}
}

float UDoorTimerWidgetBase::DoorPercent()
{
	if (IsValid(DoorRef))
	{
		return DoorRef->CurrentTime / DoorRef->TriggerWaitTime;
	}

	return 0.0f;
}
