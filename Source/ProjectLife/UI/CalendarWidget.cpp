// Fill out your copyright notice in the Description page of Project Settings.


#include "CalendarWidget.h"
#include "Components/UniformGridPanel.h"
#include "../GamePlay/GameTimeStruct.h"
#include "../ProjectLIfeGameInstance.h"
#include "CalendarDummySlot.h"
#include "CalendarDateSlot.h"

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

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());
	if (IsValid(gameInstance))
	{
		FInGameTime gameTime = gameInstance->GameTime;

		int32 year = gameTime.Year;
		int32 month = gameTime.Month;

		int32 totalDay = (gameTime.Year * FInGameTime::MAXMONTH * FInGameTime::MAXDAY)
			+ ((gameTime.Month - 1) * FInGameTime::MAXDAY);

		//sun = 0, mon = 1 , tues = 2, weds = 3, thur = 4 , fri = 5, sat = 6
		int32 firstDayOfMonth = totalDay % FInGameTime::WEEK;


		int32 row = 0;
		int32 column = 0;
		int32 currentDay = 1;


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
		while (currentDay <= gameTime.MAXDAY)
		{
			UCalendarDateSlot* dateSlot;
			if (currentDay == gameInstance->GameTime.Day)
			{
				dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlot_Today_Class);
			}
			else
			{
				dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlotClass);
			}


			//UCalendarDateSlot* dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlotClass);
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
