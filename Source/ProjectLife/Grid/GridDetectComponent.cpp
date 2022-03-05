// Fill out your copyright notice in the Description page of Project Settings.


#include "GridDetectComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "GridActor.h"
// Sets default values for this component's properties
UGridDetectComponent::UGridDetectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGridDetectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGridDetectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	DetectGrid();
}

AGridActor* UGridDetectComponent::DetectGrid()
{
	//UE_LOG(LogTemp, Warning, TEXT("DetectGrid()"));

	if (!GetOwner())
	{
		return nullptr;
	}

	TArray<TEnumAsByte<EObjectTypeQuery>> objects;
	objects.Add(EObjectTypeQuery::ObjectTypeQuery9); // Grid object type.

	FVector traceStart = GetOwner()->GetActorLocation() + FVector(0.0f, 0.0f, -50.0f); // A little Downward of Trace Start Location.
	FVector traceEnd = traceStart + GetOwner()->GetActorForwardVector() * 100.0f + GetOwner()->GetActorUpVector() * -50.0f;

	TArray<AActor*> ignores;

	FHitResult hit;
	bool result = UKismetSystemLibrary::LineTraceSingleForObjects(
		GetWorld(),
		traceStart,
		traceEnd,
		objects,
		true,
		ignores,
		EDrawDebugTrace::None,
		//EDrawDebugTrace::ForDuration,
		hit,
		true,
		FLinearColor::Red,
		FLinearColor::Blue,
		2.0f
	);

	if (result)
	{
		AGridActor* gridActor = Cast<AGridActor>(hit.GetActor());
		if (IsValid(gridActor))
		{
			gridActor->DrawValidGridMesh();
			//draw grid valid mesh?
			//UE_LOG(LogTemp, Warning, TEXT("GridDetection OK."));
			return gridActor;
		}
	}

	return nullptr;
}

