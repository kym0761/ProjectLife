// Fill out your copyright notice in the Description page of Project Settings.


#include "GameTimeWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/KismetTextLibrary.h"
#include "Engine/DataTable.h"
#include "GamePlay/ProjectLifeGameState.h"
#include "Kismet/GameplayStatics.h"

void UGameTimeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitGameTimeWidget();
}

void UGameTimeWidget::InitGameTimeWidget()
{
	if (TextBlock_Year)
	{
		TextBlock_Year->TextDelegate.BindDynamic(this, &UGameTimeWidget::SetYearText);
		TextBlock_Year->SynchronizeProperties();
	}

	if (TextBlock_Month)
	{
		TextBlock_Month->TextDelegate.BindDynamic(this, &UGameTimeWidget::SetMonthText);
		TextBlock_Month->SynchronizeProperties();
	}

	if (TextBlock_Day)
	{
		TextBlock_Day->TextDelegate.BindDynamic(this, &UGameTimeWidget::SetDayText);
		TextBlock_Day->SynchronizeProperties();
	}

	if (TextBlock_Hour)
	{
		TextBlock_Hour->TextDelegate.BindDynamic(this, &UGameTimeWidget::SetHourText);
		TextBlock_Hour->SynchronizeProperties();
	}

	if (TextBlock_Minute)
	{
		TextBlock_Minute->TextDelegate.BindDynamic(this, &UGameTimeWidget::SetMinuteText);
		TextBlock_Minute->SynchronizeProperties();
	}

	GameStateRef = Cast<AProjectLifeGameState>(UGameplayStatics::GetActorOfClass(GetWorld(), AProjectLifeGameState::StaticClass()));

}

FText UGameTimeWidget::SetYearText()
{
	if (IsValid(GameStateRef))
	{
		int32 year = GameStateRef->InGameTime.Year;

		FText text = UKismetTextLibrary::Conv_IntToText(year, false, true, 1, 324);

		FString temp = UKismetTextLibrary::Conv_TextToString(text);

		switch (year)
		{
		case 1 :
		temp += FString("st");
		break;
		case 2 :
			temp += FString("nd");
			break;
		case 3:
			temp += FString("rd");
			break;
		default:
			temp += FString("th");
			break;
		}

		return UKismetTextLibrary::Conv_StringToText(temp);
	}

	return FText();
}

FText UGameTimeWidget::SetMonthText()
{
	if (IsValid(GameStateRef) && IsValid(MonthTitleDataTable))
	{
		int32 month = GameStateRef->InGameTime.Month;
		FString monthString = FString::FromInt(month);
		FMonthRow* monthRow = MonthTitleDataTable->FindRow<FMonthRow>(FName(*monthString), "");

		if (monthRow != nullptr)
		{
			return FText::FromString( *monthRow->MonthName);
		}
	}
	return FText();
}

FText UGameTimeWidget::SetDayText()
{
	if (IsValid(GameStateRef))
	{
		int32 day = GameStateRef->InGameTime.Day;

		FText text = UKismetTextLibrary::Conv_IntToText(day, false, true, 1, 324);

		FString temp = UKismetTextLibrary::Conv_TextToString(text);

		switch (day)
		{
		case 1:
			temp += FString("st");
			break;
		case 2:
			temp += FString("nd");
			break;
		case 3:
			temp += FString("rd");
			break;
		default:
			temp += FString("th");
			break;
		}

		return UKismetTextLibrary::Conv_StringToText(temp);
	}

	return FText();
}

FText UGameTimeWidget::SetHourText()
{
	if (IsValid(GameStateRef))
	{
		int32 hour = GameStateRef->InGameTime.Hour;
		return UKismetTextLibrary::Conv_IntToText(hour, false, true, 2, 324);
	}
	return FText();
}

FText UGameTimeWidget::SetMinuteText()
{
	if (IsValid(GameStateRef))
	{
		int32 minute = GameStateRef->InGameTime.Minute;
		return UKismetTextLibrary::Conv_IntToText(minute, false, true, 2, 324);
	}

	return FText();
}
