// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LinkManager.generated.h"

class ULinkComponent;
class ALinkEdge;


UCLASS()
class PROJECTLIFE_API ALinkManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALinkManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Refs")
		TArray<ULinkComponent*> Links;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
		TSubclassOf<ALinkEdge> EdgeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Refs")
		float MaxDistanceForEdge;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
