// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityComponent.h"
#include "Ability.h"
//#include "../Base/StatComponent.h"

// Sets default values for this component's properties
UAbilityComponent::UAbilityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAbilityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAbilityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAbilityComponent::AddAbility(AAbility* AbilityToAdd)
{
	AbilityMap.Add(AbilityToAdd->GetName(), AbilityToAdd);
}

void UAbilityComponent::RemoveAbility(AAbility* AbilityToRemove)
{
	AbilityMap.Remove(AbilityToRemove->GetName());
}

void UAbilityComponent::CommitAbility()
{
	//AActor* owner = GetOwner();

	//if (IsValid(owner))
	//{
	//	for (AAbility* ability : AbilityArray)
	//	{
	//		//ability;
	//	}
	//}
}

void UAbilityComponent::ReEvalueateAbility()
{
	//AActor* owner = GetOwner();

	//if (IsValid(owner))
	//{
	//	UStatComponent* statComponent = owner->FindComponentByClass<UStatComponent>();

	//	if (IsValid(statComponent))
	//	{
	//		//statComponent->

	//		//for (auto& ability : AbilityMap)
	//		//{

	//		//}
	//	}
	//}
}

