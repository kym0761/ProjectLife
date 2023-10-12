// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootingPoint.generated.h"

class UBillboardComponent;
class AItemPickup;

UCLASS()
class PROJECTLIFE_API ALootingPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALootingPoint();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UBillboardComponent> Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Looting")
		TSubclassOf<AItemPickup> ItemPickupClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Looting", Meta = (ClampMin = 0.0f, ClampMax = 100.0f))
		float ProbabilityRate;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnLooting();

};
