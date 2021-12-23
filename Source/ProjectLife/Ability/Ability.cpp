// Fill out your copyright notice in the Description page of Project Settings.


#include "Ability.h"
#include "AbilityComponent.h"
// Sets default values
AAbility::AAbility()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetCanBeDamaged(false);
}

// Called when the game starts or when spawned
void AAbility::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAbility::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAbility::SetAbilityOwner(AActor* Value)
{
	if (IsValid(Value))
	{
		AbilityOwner = Value;
	}
}

void AAbility::StartAbility()
{
	//it Called First Time When Start Ability
	//first, register Ability To Owner's AbilityComponent.
	if (IsValid(AbilityOwner))
	{
		UAbilityComponent* abilityComponent = AbilityOwner->FindComponentByClass<UAbilityComponent>();

		if (IsValid(abilityComponent))
		{
			abilityComponent->AddAbility(this);
		}
	}

	//then Begin Ability.
	BeginActive();

	//then ActivatingAbility will be turned On.
	ActivatePassive();
	
	//timer setting when it has a Duration.
	if (AbilityData.bIsInifinity == false)
	{
		CurrentDurationTime = AbilityData.Duration;
		//Timer setting
		GetWorldTimerManager().SetTimer(AbilityCountdownTimer, this, &AAbility::AbilityEndTimerFunction, 1.0f, true, 1.0f);
	}
}

void AAbility::BeginActive_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("BeginActive.. Please Override it."));
	}
}

void AAbility::ActivatePassive_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivatePassive.. Please Override it."));
	}
}

void AAbility::EndAbility_Implementation()
{
	//It may be call when Ability Actor Destroyed.

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("EndAbility.. Please Override it."));
	}
}

void AAbility::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (IsValid(AbilityOwner))
	{
		UAbilityComponent* abilityComponent = AbilityOwner->FindComponentByClass<UAbilityComponent>();
		if (IsValid(abilityComponent))
		{
			abilityComponent->RemoveAbility(this);
		}
		EndAbility();
	}
}

void AAbility::AbilityEndTimerFunction()
{
	if (CurrentDurationTime <= 0.0f)
	{
		CurrentDurationTime = 0.0f;
		GetWorldTimerManager().ClearTimer(AbilityCountdownTimer);
		Destroy();
	}
	//else
	//{
	//	//if (GEngine)
	//	//{
	//	//	FString str = TEXT("currentTime ---> ")
	//	//		+ FString::SanitizeFloat(CurrentDurationTime);

	//	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
	//	//}
	//}

	CurrentDurationTime = FMath::Clamp(CurrentDurationTime - 1.0f, 0.0f, AbilityData.Duration);
}

