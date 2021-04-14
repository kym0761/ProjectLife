// Fill out your copyright notice in the Description page of Project Settings.


#include "GridComponent.h"
#include "GridManager.h"

UGridComponent::UGridComponent()
{

}

void UGridComponent::RequestBuild(TSubclassOf<ABuildingBase> BuildingClass)
{
	AActor* owner = GetOwner();
	if (IsValid(owner))
	{
		AGridManager* gridManager = Cast<AGridManager>(owner);
		if (IsValid(gridManager))
		{
			gridManager->HandleRequestBuild(BuildingClass, this);
		}
	}
}

void UGridComponent::SetXY(int32 inX, int32 inY)
{
	X = inX;
	Y = inY;
}

void UGridComponent::Interact_Implementation(APawn* InteractCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Grid Interact()"));
}

void UGridComponent::DrawAvailable()
{
	AActor* owner = GetOwner();
	if (IsValid(owner))
	{
		AGridManager* gridManager = Cast<AGridManager>(owner);
		if (IsValid(gridManager))
		{
			gridManager->DrawAVailableMesh(this);
		}
	}
}
