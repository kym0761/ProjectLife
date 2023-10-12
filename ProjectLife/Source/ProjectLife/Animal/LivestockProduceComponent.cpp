// Fill out your copyright notice in the Description page of Project Settings.


#include "LivestockProduceComponent.h"
#include "Animal.h"
#include "Item/Item.h"

// Sets default values for this component's properties
ULivestockProduceComponent::ULivestockProduceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULivestockProduceComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULivestockProduceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AItem* ULivestockProduceComponent::Produce()
{
	if (IsValid(ProduceClass))
	{
		FTransform transform;
		transform = GetOwner()->GetActorTransform();
		AItem* produce = GetWorld()->SpawnActor<AItem>(ProduceClass, transform);
	
		AActor* owner = GetOwner();
		if (IsValid(owner))
		{
			AAnimal* animal = Cast<AAnimal>(owner);
			if (IsValid(animal))
			{
				animal->PlayInteractSound();
			}
		}

		return produce;
	}

	return nullptr;

}
