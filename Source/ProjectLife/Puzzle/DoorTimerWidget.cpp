// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorTimerWidget.h"
#include "Components/ProgressBar.h"
#include "PuzzleDoor.h"
void UDoorTimerWidget::NativeConstruct()
{

	if (TimerProgressBar)
	{
		//TimerProgressBar->PercentDelegate.BindDynamic(this, &UDoorTimerWidget::DoorPercent);
		TimerProgressBar->PercentDelegate.BindUFunction(this, TEXT("DoorPercent"));
		TimerProgressBar->SynchronizeProperties();
	}
}

float UDoorTimerWidget::DoorPercent()
{
	if (IsValid(DoorRef))
	{
		return DoorRef->CurrentTime / DoorRef->TriggerWaitTime;
	}

	return 0.0f;
}
