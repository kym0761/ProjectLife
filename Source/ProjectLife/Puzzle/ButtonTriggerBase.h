// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "PuzzleTriggerBase.h"
#include "ButtonTriggerBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AButtonTriggerBase : public APuzzleTriggerBase
{
	GENERATED_BODY()
	
public:

	AButtonTriggerBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Button;


	FTimeline TimelineHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* CurveForTimeline;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnButtonBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnButtonEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void InitializeForTimeline();

	UFUNCTION()
		void TimelineFloatFunction(float Value);

	virtual void ButtonUp(); // virtual for ResetButton. See ResetButtonTriggerBase.h
	void ButtonDown();

	void ButtonMeshUp();
	void ButtonMeshDown();

	virtual void Trigger();
};
