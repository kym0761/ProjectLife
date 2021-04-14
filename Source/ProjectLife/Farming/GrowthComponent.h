// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrowthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UGrowthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrowthComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		bool bAlreadyGrewUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 MaxGrowthLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 GrowthLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 GrowthLevelThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 CurrentGrowth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 Day;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Growth")
		int32 NumberOfHarvest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Grow();
	void Fruit();
};
