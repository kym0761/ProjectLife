// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarWidget.generated.h"

class UUniformGridPanel;
class UCalendarDateSlot;
class UCalendarDummySlot;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCalendarWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	
	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UUniformGridPanel> CalendarGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime")
		TSubclassOf<UCalendarDateSlot> CalendarDateSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime")
		TSubclassOf< UCalendarDummySlot> CalendarDummySlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameTime")
		TSubclassOf<UCalendarDateSlot> CalendarDateSlot_Today_Class;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Year;

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UTextBlock> TextBlock_Month;

public:

	virtual void NativeConstruct() override;

	void InitCalendar();

protected:

	virtual bool Initialize() override;

};
