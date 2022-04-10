// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CalendarDateSlot.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCalendarDateSlot : public UUserWidget
{
	GENERATED_BODY()
public :

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SlotDayNumber;

public:

	void SetDay(int32 Day);

};
