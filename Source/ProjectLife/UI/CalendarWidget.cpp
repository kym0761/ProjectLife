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
	if (!(IsValid(CalendarGridPanel) && IsValid(CalendarDateSlotClass) && IsValid(CalendarDateSlotClass)))
	{
		return;
	}

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());
	if (IsValid(gameInstance))
	{
		FGameTime gameTime = gameInstance->GameTime;

		int32 year = gameTime.Year;
		int32 month = gameTime.Month;

		if (GEngine)
		{
			FString str = TEXT("year : ") + FString::FromInt(year);

			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
		}

		if (GEngine)
		{
			FString str = TEXT("month : ") + FString::FromInt(month);

			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
		}

		int32 totalDay = (gameTime.Year * gameTime.MAXMONTH * gameTime.MAXDAY)
			+ ((gameTime.Month - 1) * gameTime.MAXDAY);
			

		if (GEngine)
		{
			FString str = TEXT("totalDay : ") + FString::FromInt(totalDay);

			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
		}

		//sun = 0, mon = 1 , tues = 2, weds = 3, thur = 4 , fri = 5, sat = 6
		int32 firstDayOfMonth = totalDay % gameTime.WEEK;
		//firstDayOfMonth = firstDayOfMonth == 0 ? 7 : firstDayOfMonth;
		if (GEngine)
		{
			FString str = TEXT("firstDayOfMonth : ") + FString::FromInt(firstDayOfMonth);

			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
		}

		int32 row = 0;
		int32 column = 0;
		int32 currentDay = 1;


		for (column = 0; column < gameTime.WEEK; column++)
		{
			if (column < firstDayOfMonth)
			{
				//dummy
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

		while (currentDay <= gameTime.MAXDAY)
		{
			UCalendarDateSlot* dateSlot = CreateWidget<UCalendarDateSlot>(GetOwningPlayer(), CalendarDateSlotClass);
			if (IsValid(dateSlot))
			{
				CalendarGridPanel->AddChildToUniformGrid(dateSlot, row, column);
				column++;
				currentDay++;
			}

			if (column >= gameTime.WEEK)
			{
				row++;
				column = 0;
			}
		}

		while (column != 0 && column < gameTime.WEEK)
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
