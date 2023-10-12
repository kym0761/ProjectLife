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

	bFruited = false;
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
	if (bFruited) // 이미 다 자랐으면 Fruit가 발동하지 말아야함.
	{
		return;
	}

	if (GrowthLevel >= MaxGrowthLevel)
	{
		bFruited = true;
		
		//ToDo : 작물이 다 자라면 열매(?)를 맺어야함.
		//수확후 다시 자라는 기능 필요.
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

bool UGrowthComponent::GetFruited() const
{
	return bFruited;
}

int32 UGrowthComponent::GetGrowthLevel() const
{
	return GrowthLevel;
}

int32 UGrowthComponent::GetCurrentGrowth() const
{
	return CurrentGrowth;
}

int32 UGrowthComponent::GetDay() const
{
	return Day;
}
