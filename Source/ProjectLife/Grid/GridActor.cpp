// Fill out your copyright notice in the Description page of Project Settings.


#include "GridActor.h"
#include "Components/BoxComponent.h"
#include "components/StaticMeshComponent.h"

// Sets default values
AGridActor::AGridActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetCollisionProfileName(TEXT("Grid"));
	Box->InitBoxExtent(FVector(100.0f, 100.0f, 10.0f));
	SetRootComponent(Box);

	GridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 1.0f));
	GridMesh->SetCollisionProfileName(TEXT("NoCollision"));
	GridMesh->SetupAttachment(RootComponent);

	ValidGridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ValidGridMesh"));
	ValidGridMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
	ValidGridMesh->SetVisibility(false);
	ValidGridMesh->SetCollisionProfileName(TEXT("NoCollision"));
	ValidGridMesh->SetupAttachment(RootComponent);

	InvalidGridMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InvalidGridMesh"));
	InvalidGridMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 2.0f));
	InvalidGridMesh->SetVisibility(false);
	InvalidGridMesh->SetCollisionProfileName(TEXT("NoCollision"));
	InvalidGridMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AGridActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridActor::SetXY(int32 inX, int32 inY)
{
	X = inX;
	Y = inY;
}

void AGridActor::SetOccupying(AActor* inOccupying)
{
	if (IsValid(inOccupying))
	{
		Occupying = inOccupying;
	}
	else
	{
		Occupying = nullptr;
	}

	if (IsValid(Occupying))
	{
		DeactivateGrid();
	}
	else
	{
		ActivateGrid();
	}
}

void AGridActor::DrawValidGridMesh()
{
	if (IsValid(ValidGridMesh))
	{
		ValidGridMesh->SetVisibility(true);
	}
}

void AGridActor::ActivateGrid()
{
	if (IsValid(Box))
	{
		Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void AGridActor::DeactivateGrid()
{
	if (IsValid(Box))
	{
		Box->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

//void UGridComponent::DrawAvailable()
//{
//	AActor* owner = GetOwner();
//	if (IsValid(owner))
//	{
//		AGridManager* gridManager = Cast<AGridManager>(owner);
//		if (IsValid(gridManager))
//		{
//			gridManager->DrawAvailableMesh(this);
//		}
//	}
//}

//void AGridManager::DrawAvailableMesh(UGridComponent* InGrid)
//{
//	if (!IsValid(CurrentSeeGrid) || IsValid(InGrid) && CurrentSeeGrid != InGrid)
//	{
//		CurrentSeeGrid = InGrid;
//
//
//		if (IsValid(AvailableInstMesh))
//		{
//			int32 count = AvailableInstMesh->GetInstanceCount();
//			if (count > 0)
//			{
//				for (int32 i = 0; i < count; i++)
//				{
//					AvailableInstMesh->RemoveInstance(i);
//				}
//			}
//
//
//			FVector location = InGrid->GetRelativeLocation();
//			FTransform transform;
//			transform.SetLocation(location);
//
//			//UE_LOG(LogTemp, Warning, TEXT("%s"), *transform.ToString());
//
//			AvailableInstMesh->AddInstance(transform);
//		}
//
//
//	}
//
//
//}
//
//void AGridManager::RemoveAvailableMesh()
//{
//	CurrentSeeGrid = nullptr;
//
//	if (IsValid(AvailableInstMesh))
//	{
//		int32 count = AvailableInstMesh->GetInstanceCount();
//		if (count > 0)
//		{
//			for (int32 i = 0; i < count; i++)
//			{
//				AvailableInstMesh->RemoveInstance(i);
//			}
//		}
//	}
//
//}

//bool AGridManager::HandleRequestBuild(TSubclassOf<ABuilding> WantToBuild, UGridComponent* RootGrid)
//{
//	FBuildingInfo buildingInfo = WantToBuild.GetDefaultObject()->BuildingInfo;
//
//	if (IsValid(WantToBuild) && IsValid(RootGrid))
//	{
//		FString selectedGridKey = FString::FromInt(RootGrid->X) + FString("/") + FString::FromInt(RootGrid->Y);
//
//		if (GridMap.Contains(selectedGridKey) && (RootGrid == GridMap[selectedGridKey]))
//		{
//			int32 x = RootGrid->X;
//			int32 y = RootGrid->Y;
//
//			//check Valid Grid.
//			for (int32 i = 0; i < buildingInfo.SizeX; i++)
//			{
//				for (int32 j = 0; j < buildingInfo.SizeY; j++)
//				{
//					FString key = FString::FromInt(x + i) + FString("/") + FString::FromInt(y + j);
//					if (GridMap.Contains(key))
//					{
//						if (IsValid(GridMap[key]->Occupying))
//						{
//							if (GEngine)
//							{
//								GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Something is Occupying..."));
//							}
//							return false;
//						}
//					}
//					else //invalid Grid
//					{
//						if (GEngine)
//						{
//							GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Not Valid Grid"));
//						}
//
//						return false;
//					}
//				}
//
//			}
//
//
//			FActorSpawnParameters spawnParam;
//			ABuilding* building = GetWorld()->SpawnActor<ABuilding>(WantToBuild, RootGrid->GetComponentLocation(), FRotator::ZeroRotator, spawnParam);
//
//			building->CurrentGrid = GridMap[selectedGridKey];
//
//			for (int32 i = 0; i < buildingInfo.SizeX; i++)
//			{
//				for (int32 j = 0; j < buildingInfo.SizeY; j++)
//				{
//					FString key = FString::FromInt(x + i) + FString("/") + FString::FromInt(y + j);
//					if (GridMap.Contains(key))
//					{
//						GridMap[key]->Occupying = building;
//					}
//				}
//			}
//
//		}
//		else
//		{
//			if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Not Existed in Grid Map"));
//			}
//			return false;
//		}
//
//
//	}
//	else
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Invalid BuildingClass or RootGrid"));
//		}
//		return false;
//	}
//
//	return true;
//}
//
//bool AGridManager::HandleDeleteBuilding(ABuilding* WantToDelete)
//{
//	if (!IsValid(WantToDelete))
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Invalid Building"));
//		}
//		return false;
//	}
//
//	UGridComponent* currentGrid = WantToDelete->CurrentGrid;
//	FBuildingInfo buildingInfo = WantToDelete->BuildingInfo;
//
//	FString CurrentGridkey = FString::FromInt(currentGrid->X) + FString("/") + FString::FromInt(currentGrid->Y);
//
//	if (IsValid(currentGrid) && GridMap.Contains(CurrentGridkey) && (currentGrid == GridMap[CurrentGridkey]))
//	{
//		int32 x = currentGrid->X;
//		int32 y = currentGrid->Y;
//
//		for (int32 i = 0; i < buildingInfo.SizeX; i++)
//		{
//			for (int32 j = 0; j < buildingInfo.SizeY; j++)
//			{
//				FString key = FString::FromInt(x + i) + FString("/") + FString::FromInt(y + j);
//				if (GridMap.Contains(key))
//				{
//					GridMap[key]->Occupying = nullptr;
//				}
//			}
//		}
//
//		WantToDelete->Destroy();
//
//	}
//	else
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Invalid GridRef in BuildingActor"));
//		}
//		return false;
//	}
//
//	return true;
//}