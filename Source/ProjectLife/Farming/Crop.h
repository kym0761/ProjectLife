// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Base/InteractiveInterface.h"
#include "Crop.generated.h"

class UGrowthComponent;
class UStaticMeshComponent;
class UBoxComponent;
class AGridActor;

UCLASS()
class PROJECTLIFE_API ACrop : public AActor, public IInteractive
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrop();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		AGridActor* GridRef;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Growth")
		UGrowthComponent* GrowthComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);

	UFUNCTION(BlueprintNativeEvent)
		void GiveHarvest();
		void GiveHarvest_Implementation();
};
