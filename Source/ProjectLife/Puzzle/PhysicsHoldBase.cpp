// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHoldBase.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicCharacter.h"

// Sets default values
APhysicsHoldBase::APhysicsHoldBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetSimulatePhysics(true);
	Box->BodyInstance.bLockXRotation = true;
	Box->BodyInstance.bLockYRotation = true;
	Box->BodyInstance.bLockZRotation = true;

	Box->SetCollisionProfileName(TEXT("InteractiveCollision"));
	//Box->bDynamicObstacle = true;
	Box->SetCanEverAffectNavigation(false);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCanEverAffectNavigation(false);
}

// Called when the game starts or when spawned
void APhysicsHoldBase::BeginPlay()
{
	Super::BeginPlay();
	
	//Set DefaultPosition for ResetFunction.
	DefaultPosition = GetActorLocation();
}

// Called every frame
void APhysicsHoldBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsHoldBase::Interact_Implementation(APawn* InteractCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.0f,FColor::Black,TEXT("PhysicsHold Interact"));
	}

	 ABasicCharacter* playerCharacter = Cast<ABasicCharacter>(InteractCauser);
	 if (IsValid(playerCharacter))
	 {
		 playerCharacter->Hold(this);
	 }


}

void APhysicsHoldBase::TriggerAction_Implementation()
{
}

void APhysicsHoldBase::Reset_Implementation()
{
}

