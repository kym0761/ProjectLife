// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->InitBoxExtent(FVector(256.0f,256.0f,64.0f));
	Box->SetVisibility(true);
	Box->SetHiddenInGame(false);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	GoldIncomePerMinute = 0;
	GoldIncomeSave = 0;
	MaxGoldIncomeSave = 100;
}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GoldTimer, this, &ABuilding::MakeGold, 1.0f, true);

}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::Interact_Implementation(APawn* InteractCauser)
{
}

void ABuilding::MakeGold()
{
	GoldIncomeSave = FMath::Clamp(GoldIncomeSave + GoldIncomePerMinute, 0, MaxGoldIncomeSave);
}

