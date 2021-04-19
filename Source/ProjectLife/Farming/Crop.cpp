// Fill out your copyright notice in the Description page of Project Settings.


#include "Crop.h"
#include "GrowthComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ACrop::ACrop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("OverlapAllDynamic");
	GrowthComponent = CreateDefaultSubobject<UGrowthComponent>(TEXT("GrowthComponent"));

}

// Called when the game starts or when spawned
void ACrop::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACrop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrop::Interact_Implementation(APawn* InteractCauser)
{
	if (IsValid(GrowthComponent))
	{
		if (GrowthComponent->GrowthLevel >= GrowthComponent->MaxGrowthLevel)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f,FColor::Black,TEXT("Fruit Havest OK"));
				GiveHarvest();
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Black, TEXT("Still Not Grow Enough.."));
			}
		}
	}
}

void ACrop::GiveHarvest_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Black, TEXT("Harvest Give Off"));
	}
}
