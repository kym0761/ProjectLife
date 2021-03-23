// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHP = 100.0f;
	MaxStamina = 1000.0f;

	HP = 100.0f;
	Stamina = 1000.0f;
	// ...

	BaseAttack = 10.0f;
	AdditionalAttack = 0.0f;
	AttackCoefficient = 1.0f;

	BaseDefense = 0.0f;
	AdditionalDefense = 0.0f;
	DefenseCoefficient = 1.0f;

	CritcalHit = 0.0f;
	AdditionalCriticalHit = 0.0f;
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatComponent::DealDamage(float DamageAmount)
{
	HP = FMath::Clamp(HP - DamageAmount, 0.0f, MaxHP);
}

void UStatComponent::Heal(float HealAmount)
{
	HP = FMath::Clamp(HP + HealAmount, 0.0f, MaxHP);
}

void UStatComponent::RefillStamina(float RefillAmount)
{
	Stamina = FMath::Clamp(Stamina + RefillAmount, 0.0f, MaxStamina);
}

void UStatComponent::ClearAdditionalStat()
{
	AdditionalAttack = 0.0f;
	AdditionalDefense = 0.0f;
}

void UStatComponent::ApplyAdditionalStat(FItemDataStruct InData)
{
	AdditionalAttack += InData.Attack;
	AdditionalDefense += InData.Defense;
	AdditionalCriticalHit += InData.CriticalHit;
}

