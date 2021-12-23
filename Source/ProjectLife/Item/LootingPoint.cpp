// Fill out your copyright notice in the Description page of Project Settings.


#include "LootingPoint.h"
#include "Components/BillboardComponent.h"
#include "ItemPickup.h"

// Sets default values
ALootingPoint::ALootingPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Billboard = CreateDefaultSubobject<UBillboardComponent>(TEXT("Billboard"));
	SetRootComponent(Billboard);
	
	ProbabilityRate = 25.0f;
}

// Called when the game starts or when spawned
void ALootingPoint::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnLooting();
}

// Called every frame
void ALootingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALootingPoint::SpawnLooting()
{
	float rand = FMath::FRandRange(0.0f, 100.0f);

	if (rand <= ProbabilityRate)
	{
		if (IsValid(ItemPickupClass))
		{
			//TODO : 스폰 목록 만들고 목록대로 스폰해주기.

			GetWorld()->SpawnActor<AItemPickup>(ItemPickupClass, GetActorLocation(), GetActorRotation());
		}
	}

}

