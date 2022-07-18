// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Base/StatComponent.h"

AMeleeWeapon::AMeleeWeapon()
{
	AttackCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AttackCollision"));
	AttackCollision->SetupAttachment(RootComponent);

	AttackCollision->SetBoxExtent(FVector(5.0f,5.0f,30.0f));
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

	AttackCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeWeapon::OverlapAttackCollision);

}

void AMeleeWeapon::OverlapAttackCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Warning ! When Spawning Weapon, You must Set Owner..

	if (OtherActor != GetOwner())
	{

		if (OwnerStatComponent)
		{
			UGameplayStatics::ApplyDamage(OtherActor, OwnerStatComponent->BaseAttack, nullptr, GetOwner(), UDamageType::StaticClass());
		}
		else
		{
			UGameplayStatics::ApplyDamage(OtherActor, WeaponData.Attack, nullptr, GetOwner(), UDamageType::StaticClass());
		}

	}
}

void AMeleeWeapon::AttackStart()
{
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AMeleeWeapon::AttackEnd()
{
	AttackCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
