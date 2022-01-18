// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/InteractiveInterface.h"
#include "Components/BoxComponent.h"
#include "GridComponent.generated.h"

class ABuilding;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTLIFE_API UGridComponent : public UBoxComponent, public IInteractive
{
	GENERATED_BODY()

public:

	UGridComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		AActor* Occupying;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 X;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 Y;

public:

	void RequestBuild(TSubclassOf<ABuilding> BuildingClass);

	void SetXY(int32 inX, int32 inY);

	virtual void Interact_Implementation(APawn* InteractCauser);

	UFUNCTION(BlueprintCallable)
	void SetOccupying(AActor* inOccupying);

	void DrawAvailable();
};
