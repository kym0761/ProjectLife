// Fill out your copyright notice in the Description page of Project Settings.


#include "CalendarWidget.h"
#include "Components/UniformGridPanel.h"
#include "../GamePlay/GameTimeStruct.h"
//#include "../ProjectLIfeGameInstance.h"
#include "CalendarDummySlot.h"
#include "CalendarDateSlot.h"
#include "../GamePlay/ProjectLifeGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"

void UCalendarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitCalendar();
}

void UCalendarWidget::InitCalendar()
{
	if (!(IsValid(CalendarGridPanel) && IsValid(CalendarDateSlotClass) && IsValid(CalendarDateSlotClass) && IsValid(CalendarDateSlot_Today_Class)))
	{
		return;
	}

	if (!(IsValid(TextBlock_Year) && IsValid(TextBlock_Month)))
	{
		return;
	}


	AProjectLifeGameState* gameState = Cast<AProjectLifeGameState>(UGameplayStatics::GetActorOfClass(GetWorld(), AProjectLifeGameState::StaticClass()));
	if (IsValid(gameState))
	{
		FInGameTime inGameTime = gameState->InGameTime;

		int32 year = inGameTime.Year;
		int32 month = inGameTime.Month;

		int32 totalDay = (inGameTime.Year * FInGameTime::MAXMONTH * FInGameTime::MAXDAY)
			+ ((inGameTime.Month - 1) * FInGameTime::MAXDAY);

		//sun = 0, mon = 1 , tues = 2, weds = 3, thur = 4 , fri = 5, sat = 6
		int32 firstDayOfMonth = totalDay % FInGameTime::WEEK;


		int32 row = 0;
		int32 column = 0;
		int32 currentDay = 1;

		//UI TextBlock 추가
		TextBlock_Year->SetText(UKismetTextLibrary::Conv_IntToText(year));
		TextBlock_Month->SetText(UKismetTextLibrary::Conv_IntToText(month));

		//첫 주 더미 슬롯 추가. ex) 1일이 수요일이면 일 월 화는 더미 슬롯이어야 함.
		for (column = 0; column < FInGameTime::WEEK; column++)
		{
			if (column < firstDayOfMonth)
			{
				UCalendarDummySlot* dummySlot = CreateWidget<UCalendarDummySlot>(GetOwningPlayer(), CalendarDummySlotClass);
				if (IsValid(dummySlot))
				{
					CalendarGridPanel->AddChildToUniformGrid(dummySlot, row, column);
				}
			}
			else
			{
				break;
			}
		}

		//실제 기능을 가진 Calendar Slot
		while (currentDay <= inGameTime.MAXDAY)
		{
			UCalendarDateSlot* dateSlot;
			if (currentDay == inGameTime.Day)
			{
				dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlot_Today_Class);
			}
			else
			{
				dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlotClass);
			}

			if (IsValid(dateSlot))
			{
				CalendarGridPanel->AddChildToUniformGrid(dateSlot, row, column);
				dateSlot->SetDay(currentDay);
				column++;
				currentDay++;
			}

			if (column >= FInGameTime::WEEK)
			{
				row++;
				column = 0;
			}
		}

		//마지막 주 더미 슬롯 추가. ex) 30일이 수요일이면 목 금 토는 더미 슬롯이어야함.
		while (column != 0 && column < FInGameTime::WEEK)
		{
			UCalendarDummySlot* dummySlot = CreateWidget<UCalendarDummySlot>(GetOwningPlayer(), CalendarDummySlotClass);
			if (IsValid(dummySlot))
			{
				CalendarGridPanel->AddChildToUniformGrid(dummySlot, row, column);
				column++;
			}
		}
	}

}
