// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
UCLASS()
class PROJECTLIFE_API AGridActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGridActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		TObjectPtr<UBoxComponent> Box;

	//Crop or Building
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		TObjectPtr<AActor> Occupying;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 X;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Grid")
		int32 Y;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UStaticMeshComponent> GridMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UStaticMeshComponent> ValidGridMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		TObjectPtr<UStaticMeshComponent> InvalidGridMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void SetXY(int32 inX, int32 inY);

	UFUNCTION(BlueprintCallable)
		void SetOccupying(AActor* inOccupying);

	void DrawValidGridMesh();

	void ActivateGrid();
	void DeactivateGrid();
	
};
