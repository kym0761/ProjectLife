// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTimeWidget.generated.h"

class UTextBlock;
class UProjectLIfeGameInstance;
class UDataTable;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UGameTimeWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Year;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Month;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Day;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Hour;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_Minute;

	UPROPERTY()
		UProjectLIfeGameInstance* GameInstanceRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime")
		UDataTable* MonthTitleDataTable;

	virtual void NativeConstruct() override;

	UFUNCTION()
		FText SetYearText();

	UFUNCTION()
		FText SetMonthText();

	UFUNCTION()
		FText SetDayText();

	UFUNCTION()
		FText SetHourText();

	UFUNCTION()
		FText SetMinuteText();

};
