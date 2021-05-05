// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

class UGridComponent;
class UBillboardComponent;
class ABuildingBase;
class UInstancedStaticMeshComponent;
UCLASS()
class PROJECTLIFE_API AGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridManager();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Component")
		UBillboardComponent* DefaultRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", Meta = (ClampMin = 0, ClampMax = 100))
		int32 X;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", Meta = (ClampMin = 0, ClampMax = 100))
		int32 Y;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn", Meta = (ClampMin = 0, ClampMax = 1000))
		float Offset;

	//May Not need to be Seen in Blueprint.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn")
		TMap<FString, UGridComponent*> GridMap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		TSubclassOf<UGridComponent> GridCompClass;

	//You can See whether that This Grid Can be used or not.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UInstancedStaticMeshComponent* AvailableInstMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawn")
		UGridComponent* CurrentSeeGrid;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	* Spawn Grids With Your Setting.
	*/
	UFUNCTION(CallInEditor, Category = "Spawn")
		void SpawnGrids();

	void SetNearGrids();

	/*
	* Remove All Grids
	*/
	UFUNCTION(CallInEditor, Category = "Spawn")
		void RemoveAllGrids();

	void HandleRequestBuild(TSubclassOf<ABuildingBase> WantToBuild, UGridComponent* RootGrid);

	void DrawAvailableMesh(UGridComponent* InGrid);
	void RemoveAvailableMesh();
};
