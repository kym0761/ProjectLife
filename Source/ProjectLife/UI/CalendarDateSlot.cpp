// Fill out your copyright notice in the Description page of Project Settings.


#include "CalendarDateSlot.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UCalendarDateSlot::SetDay(int32 Day)
{
	if(IsValid(SlotDayNumber))
	{
		SlotDayNumber->SetText(UKismetTextLibrary::Conv_IntToText(Day));
	}
}
