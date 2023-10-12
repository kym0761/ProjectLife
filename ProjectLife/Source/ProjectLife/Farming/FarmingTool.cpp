// Fill out your copyright notice in the Description page of Project Settings.


#include "FarmingTool.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
AFarmingTool::AFarmingTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Box);
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AFarmingTool::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFarmingTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFarmingTool::SetFarmingToolOwner(AActor* InActor)
{
	if (IsValid(InActor))
	{
		FarmingToolOwner = InActor;
	}
}

