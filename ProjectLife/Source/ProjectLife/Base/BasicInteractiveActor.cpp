// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInteractiveActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABasicInteractiveActor::ABasicInteractiveActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

}

// Called when the game starts or when spawned
void ABasicInteractiveActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABasicInteractiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicInteractiveActor::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Log, TEXT("C++ InterActive() Function in %s"), *GetName());
}

