// Fill out your copyright notice in the Description page of Project Settings.


#include "Bed.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABed::ABed()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->InitBoxExtent(FVector(64.0f));
	//Box->SetCollisionProfileName(TEXT("Item"));
	//Collision->SetVisibility(false);
	//Box->ShapeColor = FColor::Black;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ABed::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABed::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Log, TEXT("Bed Need The Real Function."));
}

