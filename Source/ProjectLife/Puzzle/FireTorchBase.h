// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsHoldBase.h"
#include "FireTorchBase.generated.h"

class UNiagaraComponent;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API AFireTorchBase : public APhysicsHoldBase, public ICombustible
{
	GENERATED_BODY()
	
public:

	AFireTorchBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		UBoxComponent* FireOverlap;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		UNiagaraComponent* FireEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Effect")
		bool bFireOn;

	void FireOn();

	void FireOff();

	virtual void Combust_Implementation();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
