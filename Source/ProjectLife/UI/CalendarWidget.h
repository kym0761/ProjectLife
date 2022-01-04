// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarWidget.generated.h"

class UUniformGridPanel;
class UCalendarDateSlot;
class UCalendarDummySlot;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCalendarWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	
	UPROPERTY(Meta = (BindWidget))
		UUniformGridPanel* CalendarGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
		TSubclassOf<UCalendarDateSlot> CalendarDateSlotClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Calendar")
		TSubclassOf< UCalendarDummySlot> CalendarDummySlotClass;

	virtual void NativeConstruct() override;

	void InitCalendar();
};
