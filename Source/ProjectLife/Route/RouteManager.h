// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RouteManager.generated.h"

class ARouteNode;

UCLASS()
class PROJECTLIFE_API ARouteManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARouteManager();

	//TArray<ARouteNode*> Routes;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//ARouteNode* FindNearestRouteNode(AActor* Requestor);
	//void FindRoute();
};
