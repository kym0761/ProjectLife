// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Base/StatComponent.h"
// Sets default values
ABasicWeapon::ABasicWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);	
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));

}

// Called when the game starts or when spawned
void ABasicWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		OwnerStatComponent = GetOwner()->FindComponentByClass<UStatComponent>();
	}
}

// Called every frame
void ABasicWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasicWeapon::AttackStart()
{
	UE_LOG(LogTemp, Warning, TEXT("C++ BasicWeapon AttackStart()"));
}

void ABasicWeapon::AttackEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("C++ BasicWeapon AttackEnd()"));
}

