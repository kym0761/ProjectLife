// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorTimerWidgetBase.generated.h"

class APuzzleDoorBase;
class UProgressBar;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UDoorTimerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* TimerProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		APuzzleDoorBase* DoorRef;

	virtual void NativeConstruct() override;

	UFUNCTION()
	float DoorPercent();
};
