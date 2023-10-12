// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WaterDeliveryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UWaterDeliveryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWaterDeliveryComponent();

	UPROPERTY()
		bool bIsActivated;

	UPROPERTY()
		TArray<TObjectPtr<UWaterDeliveryComponent>> Connected;

	//물을 공급해주고 있는 WaterDeliveryComponent.
	UPROPERTY()
		TObjectPtr<UWaterDeliveryComponent> Forwarding;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void WaterDelivery();
	void StopWatering();
	void SetActivate(bool InVal);
	bool GetActivate() const;
};
