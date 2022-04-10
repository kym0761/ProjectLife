// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SpeechWidgetComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTLIFE_API USpeechWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	USpeechWidgetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Category = "Speech")
	void SpeechTrigger(FString InString);
	
	UFUNCTION()
	void SpeechEnd();
};
