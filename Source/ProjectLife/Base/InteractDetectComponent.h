// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "InteractDetectComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UInteractDetectComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:

	UInteractDetectComponent();

private:
	UPROPERTY()
		AActor* HasInteractive;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	void CheckInteract();

	UFUNCTION()
		void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
		void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	AActor* GetInteractiveActor() const;
};
