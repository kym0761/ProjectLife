// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractiveInterface.h"
#include "GameFramework/Actor.h"
#include "BasicInteractiveActor.generated.h"

class USkeletalMeshComponent;
class USphereComponent;

UCLASS()
class PROJECTLIFE_API ABasicInteractiveActor : public AActor, public IInteractive
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasicInteractiveActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USkeletalMeshComponent* Mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation(APawn* InteractCauser);
};
