// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleTriggerBase.h"
#include "PuzzleInterfaces.h"
#include "FireStandBase.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class UNiagaraComponent;
class UNiagaraSystem;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AFireStandBase : public APuzzleTriggerBase, public ITriggerable, public IResetable
{
	GENERATED_BODY()

public:

	AFireStandBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Stand;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UWidgetComponent* Widget;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UNiagaraComponent* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		bool bUseTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		bool bOffImmediately;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timeline")
		float TriggerWaitTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timeline")
		float CurrentTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reset")
		UNiagaraSystem* ResetNiagaraSystem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TriggerAction_Implementation();

	virtual void Reset_Implementation();

	void TurnOnFire();
	void TurnOffFire();
};
