// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameTimeWidget.generated.h"

class UTextBlock;
class AProjectLifeGameState;
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
		TObjectPtr<UTextBlock> TextBlock_Year;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Month;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Day;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Hour;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Minute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime")
		TObjectPtr<UDataTable> MonthTitleDataTable;

private:

	UPROPERTY()
		TObjectPtr<AProjectLifeGameState> GameStateRef;

public:
	virtual void NativeConstruct() override;

	void InitGameTimeWidget();

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

protected:

	virtual bool Initialize() override;
};
