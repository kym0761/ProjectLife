// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DoorTimerWidget.generated.h"

class APuzzleDoor;
class UProgressBar;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UDoorTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		TObjectPtr<UProgressBar> TimerProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		TObjectPtr<APuzzleDoor> DoorRef;

public:

	virtual void NativeConstruct() override;

	UFUNCTION()
	float DoorPercent();
};
