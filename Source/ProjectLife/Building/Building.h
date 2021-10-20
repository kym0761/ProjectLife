// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "BuildingInfo.h"
#include "Building.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UGridComponent;

UCLASS()
class PROJECTLIFE_API ABuilding : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		int32 GoldIncomePerMinute;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Building")
		int32 GoldIncomeSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		int32 MaxGoldIncomeSave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
		FBuildingInfo BuildingInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		UGridComponent* CurrentGrid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);

	FTimerHandle GoldTimer;

	void MakeGold();
};
