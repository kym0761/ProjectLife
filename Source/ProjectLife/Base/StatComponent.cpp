// Fill out your copyright notice in the Description page of Project Settings.


#include "StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 100.0f;
	MaxStamina = 1000.0f;

	HP = 100.0f;
	Shield = 0.0f;
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
	float remainDamage = DamageAmount;

	//if there is shield Amount, Apply Damage to shield first.
	if (Shield > 0.0f)
	{
		float currentShield = Shield;

		if (Shield >= remainDamage)
		{
			Shield = FMath::Clamp(Shield - remainDamage, 0.0f, 1000000.0f); //1,000,000 is Enough?
			remainDamage = 0.0f;
		}
		else
		{
			remainDamage -= Shield;
			Shield = 0.0f;
		}		 
	}


	HP = FMath::Clamp(HP - remainDamage, 0.0f, MaxHP);
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
	//Not Finished.
	AdditionalAttack = 0.0f;
	AdditionalDefense = 0.0f;
	AdditionalCriticalHit = 0.0f;
}

void UStatComponent::ApplyAdditionalStat(UEquipmentItemData* InData)
{
	//Not Finished.
	if (IsValid(InData))
	{
		AdditionalAttack += InData->Attack;
		AdditionalDefense += InData->Defense;
		AdditionalCriticalHit += InData->CriticalHit;
	}
}

