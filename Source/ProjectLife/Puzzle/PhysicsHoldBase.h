// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Base/InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "PuzzleInterfaces.h"
#include "PhysicsHoldBase.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class PROJECTLIFE_API APhysicsHoldBase : public AActor, public IInteractive, public ITriggerable, public IResetable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APhysicsHoldBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		FVector DefaultPosition;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);

	bool SetHoldStatus(bool Status);

	void ThrowToDirection(FVector Direction);


	virtual void TriggerAction_Implementation();

	virtual void Reset_Implementation();

};
