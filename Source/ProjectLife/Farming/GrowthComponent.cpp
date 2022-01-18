// Fill out your copyright notice in the Description page of Project Settings.


#include "GrowthComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values for this component's properties
UGrowthComponent::UGrowthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	bAlreadyGrewUp = false;
	MaxGrowthLevel = 3;
	GrowthLevel = 0;
	GrowthLevelThreshold = 3;
	CurrentGrowth = 0;
	Day = 0;
	NumberOfHarvest = 1;
}


// Called when the game starts
void UGrowthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	SetOwnerMesh();
}


// Called every frame
void UGrowthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrowthComponent::Grow()
{
	Day += 1;
	CurrentGrowth += 1;

	GrowthLevel = FMath::Clamp(CurrentGrowth / GrowthLevelThreshold, 0, MaxGrowthLevel);

	//if (CurrentGrowth >= GrowthLevelThreshold)
	//{
	//	GrowthLevel = FMath::Clamp(GrowthLevel + 1, 0, MaxGrowthLevel);
	//	CurrentGrowth = 0;
	//}
	SetOwnerMesh();

	Fruit();
}

void UGrowthComponent::Fruit()
{
	if (GrowthLevel >= MaxGrowthLevel)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fruit"));
	}

}

void UGrowthComponent::SetOwnerMesh()
{
	AActor* owner = GetOwner();
	if (IsValid(owner))
	{
		UStaticMeshComponent* meshComp = owner->FindComponentByClass<UStaticMeshComponent>();
		if (IsValid(meshComp) && GrowthMeshs.IsValidIndex(GrowthLevel))
		{
			meshComp->SetStaticMesh(GrowthMeshs[GrowthLevel]);
		}
	}
}
