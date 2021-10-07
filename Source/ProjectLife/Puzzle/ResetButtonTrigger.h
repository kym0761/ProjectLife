// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ButtonTrigger.h"
#include "ResetButtonTrigger.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AResetButtonTrigger : public AButtonTrigger
{
	GENERATED_BODY()

public:
	AResetButtonTrigger();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ButtonUp() override;

	virtual void Trigger() override;
};
