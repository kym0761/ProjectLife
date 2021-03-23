// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTimerWidgetBase.h"
#include "Components/ProgressBar.h"
#include "FireStandBase.h"
void UFireTimerWidgetBase::NativeConstruct()
{
	if (TimerProgressBar)
	{
		//Equal => TimerProgressBar->PercentDelegate.BindDynamic(this, &UDoorTimerWidgetBase::DoorPercent);
		TimerProgressBar->PercentDelegate.BindUFunction(this, TEXT("FirePercent"));
		TimerProgressBar->SynchronizeProperties();
	}
}

float UFireTimerWidgetBase::FirePercent()
{
	if (IsValid(FireRef))
	{
		return FireRef->CurrentTime / FireRef->TriggerWaitTime;
	}

	return 0.0f;
}
