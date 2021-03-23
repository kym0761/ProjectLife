// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FireTimerWidgetBase.generated.h"

class UProgressBar;
class AFireStandBase;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UFireTimerWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UProgressBar* TimerProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
		AFireStandBase* FireRef;

	virtual void NativeConstruct() override;

	UFUNCTION()
		float FirePercent();
};
