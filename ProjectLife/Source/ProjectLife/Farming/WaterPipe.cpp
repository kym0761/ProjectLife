// Fill out your copyright notice in the Description page of Project Settings.


#include "WaterPipe.h"
#include "WaterDeliveryComponent.h"

// Sets default values
AWaterPipe::AWaterPipe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterDeliveryComponent = CreateDefaultSubobject<UWaterDeliveryComponent>(TEXT("WaterDeliveryComponent"));

}

// Called when the game starts or when spawned
void AWaterPipe::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWaterPipe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

