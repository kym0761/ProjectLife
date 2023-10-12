// Fill out your copyright notice in the Description page of Project Settings.


#include "FireTimerWidget.h"
#include "Components/ProgressBar.h"
#include "FireStand.h"
void UFireTimerWidget::NativeConstruct()
{
	if (TimerProgressBar)
	{
		//Equal == 
		//TimerProgressBar->PercentDelegate.BindDynamic(this, &UFireTimerWidget::FirePercent);
		TimerProgressBar->PercentDelegate.BindUFunction(this, TEXT("FirePercent"));
		TimerProgressBar->SynchronizeProperties();
	}
}

float UFireTimerWidget::FirePercent()
{
	if (IsValid(FireRef))
	{
		return FireRef->CurrentTime / FireRef->TriggerWaitTime;
	}

	return 0.0f;
}
