// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleInterfaces.h"
#include "PuzzleDoorBase.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class APuzzleTriggerBase;
class UCurveFloat;
class UWidgetComponent;
class UNiagaraSystem;

UCLASS()
class PROJECTLIFE_API APuzzleDoorBase : public AActor, public ITriggerable, public IResetable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleDoorBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
		TArray<APuzzleTriggerBase*> TriggerArray;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
		bool bDoorOpen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		bool bUseTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		bool bOpenPermanently;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
		float TriggerWaitTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trigger")
		float CurrentTime;

	FTimeline TimelineHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		UCurveFloat* CurveForTimeline;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
		UNiagaraSystem* ResetNiagaraSystem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TriggerAction_Implementation();

	void InitializeForTimeline();

	UFUNCTION()
	void TimelineFloatFunction(float Value);

	void OpenDoor();
	void CloseDoor();

	virtual void Reset_Implementation();
};
