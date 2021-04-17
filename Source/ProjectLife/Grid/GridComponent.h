// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/Base.h"
#include "Components/BoxComponent.h"
#include "GridComponent.generated.h"

class ABuildingBase;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTLIFE_API UGridComponent : public UBoxComponent, public IInteractive
{
	GENERATED_BODY()

public:

	UGridComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
		AActor* Occupying;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
		int32 X;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
		int32 Y;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Variable")
		TArray<UGridComponent*> NearGrids;

public:

	void RequestBuild(TSubclassOf<ABuildingBase> BuildingClass);

	void SetXY(int32 inX, int32 inY);

	virtual void Interact_Implementation(APawn* InteractCauser);

	UFUNCTION(BlueprintCallable)
	void SetOccupying(AActor* inOccupying);

	void DrawAvailable();
};
