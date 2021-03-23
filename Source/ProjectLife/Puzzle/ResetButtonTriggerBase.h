// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonTriggerBase.h"
#include "ResetButtonTriggerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AResetButtonTriggerBase : public AButtonTriggerBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ButtonUp() override;

	virtual void Trigger() override;
};
