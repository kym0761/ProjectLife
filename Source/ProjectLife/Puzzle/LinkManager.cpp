// Fill out your copyright notice in the Description page of Project Settings.


#include "LinkManager.h"
#include "Kismet/GameplayStatics.h"
#include "LinkHoldBase.h"
#include "LinkTriggerBase.h"
#include "LinkComponent.h"
#include "LinkEdgeBase.h"

// Sets default values
ALinkManager::ALinkManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxDistanceForEdge = 500.0f;
}

// Called when the game starts or when spawned
void ALinkManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALinkManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

