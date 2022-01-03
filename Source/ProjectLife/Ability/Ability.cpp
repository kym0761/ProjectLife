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
	ActivateActiveEffect();

	//then PassiveAbility will be turned On.
	ActivatePassiveEffect();
	
	//timer setting when it has a Duration.
	switch (AbilityData.AbilityDurabilityType)
	{
	case EAbilityDurabilityType::Once:
		DestroyAbilityWithEndEffect();
		break;
	case EAbilityDurabilityType::Limited:
		CurrentDurationTime = AbilityData.Duration;
		//Timer setting for End
		GetWorldTimerManager().SetTimer(AbilityCountdownTimer, this, &AAbility::AbilityEndTimerFunction, 1.0f, true, 1.0f);
		break;
	case EAbilityDurabilityType::Infinite:
		//Do Nothing.
		break;
	default:
		break;
	}

}

void AAbility::ActivateActiveEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivateActiveEffect.. Please Override it."));
	}
}

void AAbility::ActivatePassiveEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivatePassive.. Please Override it."));
	}
}

void AAbility::EndAbility_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("EndAbility.. Please Override it."));
	}
}

void AAbility::ActivateEndEffect_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, TEXT("ActivateEndEffect.. Please Override it."));
	}
}

void AAbility::DestroyAbilityWithNoEndEffect()
{
	if (GetWorldTimerManager().IsTimerActive(AbilityCountdownTimer))
	{
		AbilityCountdownTimer.Invalidate();
		GetWorldTimerManager().ClearTimer(AbilityCountdownTimer);
	}
	Destroy();
}

void AAbility::DestroyAbilityWithEndEffect()
{
	if (GetWorldTimerManager().IsTimerActive(AbilityCountdownTimer))
	{
		AbilityCountdownTimer.Invalidate();
		GetWorldTimerManager().ClearTimer(AbilityCountdownTimer);
	}
	ActivateEndEffect();
	Destroy();
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
		DestroyAbilityWithEndEffect();
	}
	else
	{
		if (GEngine)
		{
			FString str = TEXT("currentTime : ")
				+ FString::SanitizeFloat(CurrentDurationTime);

			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Magenta, str);
		}
	}

	CurrentDurationTime = FMath::Clamp(CurrentDurationTime - 1.0f, 0.0f, AbilityData.Duration);
}

