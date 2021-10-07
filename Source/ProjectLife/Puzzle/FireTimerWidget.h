// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FireTimerWidget.generated.h"

class UProgressBar;
class AFireStand;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UFireTimerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* TimerProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		AFireStand* FireRef;

	virtual void NativeConstruct() override;

	UFUNCTION()
		float FirePercent();
};
