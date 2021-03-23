// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABuildingBase::ABuildingBase()
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
void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GoldTimer, this, &ABuildingBase::MakeGold, 1.0f, true);

}

// Called every frame
void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuildingBase::Interact_Implementation(APawn* InteractCauser)
{
}

void ABuildingBase::MakeGold()
{
	GoldIncomeSave = FMath::Clamp(GoldIncomeSave + GoldIncomePerMinute, 0, MaxGoldIncomeSave);
}

