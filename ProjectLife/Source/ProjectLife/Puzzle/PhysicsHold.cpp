// Fill out your copyright notice in the Description page of Project Settings.


#include "PhysicsHold.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Base/BasicCharacter.h"

// Sets default values
APhysicsHold::APhysicsHold()
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
void APhysicsHold::BeginPlay()
{
	Super::BeginPlay();
	
	//Set DefaultPosition for ResetFunction.
	DefaultPosition = GetActorLocation();
}

// Called every frame
void APhysicsHold::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APhysicsHold::Interact_Implementation(APawn* InteractCauser)
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

void APhysicsHold::TriggerAction_Implementation()
{
}

void APhysicsHold::Reset_Implementation()
{
}

