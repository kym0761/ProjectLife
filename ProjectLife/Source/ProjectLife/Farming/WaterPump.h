// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterPump.generated.h"

class UWaterDeliveryComponent;

UCLASS()
class PROJECTLIFE_API AWaterPump : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterPump();

	TObjectPtr<UWaterDeliveryComponent> WaterDeliveryComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
