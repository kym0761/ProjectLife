// Fill out your copyright notice in the Description page of Project Settings.


#include "GridManager.h"
#include "Components/BillboardComponent.h"
#include "GridComponent.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AGridManager::AGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<UBillboardComponent>(TEXT("DefaultRoot"));
	SetRootComponent(DefaultRoot);


	AvailableInstMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("AvailableInstMesh"));
	AvailableInstMesh->SetupAttachment(RootComponent);
	AvailableInstMesh->SetCollisionProfileName(TEXT("NoCollision"));


	X = 0;
	Y = 0;

	Offset = 130.0f;
}

// Called when the game starts or when spawned
void AGridManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGridManager::SpawnGrids()
{
	//Remove if there are Not Valid Grid Components.
	RemoveAllGrids();

	if (!IsValid(GridCompClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("There is no Grid Component Class. Please Set In Blueprint."));
		return;
	}

	//Actual Spawn Grids.
	for (int32 i = 0; i < X; i++)
	{
		for (int32 j = 0; j < Y; j++)
		{
			FString compNamestr = FString::FromInt(i) + FString("/") + FString::FromInt(j);
			FName compName = FName(*compNamestr);
			UGridComponent* grid = NewObject<UGridComponent>(this, GridCompClass, compName);
			if (IsValid(grid))
			{
				grid->SetupAttachment(RootComponent);
				FVector location = FVector(i * Offset, j * Offset, 0.0f);
				grid->SetRelativeLocation(location);
				grid->SetXY(i, j);
				grid->RegisterComponent();

				//Add In GridMap.
				GridMap.Add(compNamestr, grid);
			}
		}
	}

	SetNearGrids();

}

void AGridManager::SetNearGrids()
{
	for (TPair<FString, UGridComponent*> gridPair : GridMap)
	{
		UGridComponent* grid = gridPair.Value;

		int32 x = grid->X;
		int32 y = grid->Y;

		FString keyLeft = FString::FromInt(x) + FString("/") + FString::FromInt(y - 1);
		bool bHasLeft = GridMap.Contains(keyLeft);

		FString keyRight = FString::FromInt(x) + FString("/") + FString::FromInt(y + 1);
		bool bHasRight = GridMap.Contains(keyRight);

		FString keyUp = FString::FromInt(x + 1) + FString("/") + FString::FromInt(y);
		bool bHasUp = GridMap.Contains(keyUp);

		FString keyDown = FString::FromInt(x - 1) + FString("/") + FString::FromInt(y);
		bool bHasDown = GridMap.Contains(keyDown);


		if (bHasLeft)
		{
			grid->NearGrids.Add(GridMap[keyLeft]);
		}

		if (bHasRight)
		{
			grid->NearGrids.Add(GridMap[keyRight]);
		}

		if (bHasUp)
		{
			grid->NearGrids.Add(GridMap[keyUp]);
		}

		if (bHasDown)
		{
			grid->NearGrids.Add(GridMap[keyDown]);
		}
	}


}

void AGridManager::RemoveAllGrids()
{
	//Remove Grids in Gridmap.
	if (GridMap.Num() > 0)
	{
		for (TPair<FString, UGridComponent*> i : GridMap)
		{
			if (IsValid(i.Value))
			{
				i.Value->UnregisterComponent();
				i.Value->DestroyComponent();
			}
		}
		GridMap.Empty();
	}

	//Destroy if there is any Garbage..
	TArray<UGridComponent*> gridComps;
	GetComponents(gridComps);

	if (gridComps.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("There is some Garbages. So these are will be Deleted."));

		for (UGridComponent* i : gridComps)
		{
			if (IsValid(i))
			{
				i->UnregisterComponent();
				i->DestroyComponent();
			}
		}
	}

}

void AGridManager::HandleRequestBuild(TSubclassOf<ABuildingBase> WantToBuild, UGridComponent* RootGrid)
{


	//FSize size = WantToBuild.GetDefaultObject()->Size;

	//if (IsValid(WantToBuild) && IsValid(SelectedGrid))
	//{
	//	FString selectedGridKey = FString::FromInt(SelectedGrid->X) + FString("/") + FString::FromInt(SelectedGrid->Y);

	//	if (GridMap.Contains(selectedGridKey))
	//	{
	//		bool bCanBuild = true;

	//		int x = SelectedGrid->X;
	//		int y = SelectedGrid->Y;

	//		for (int32 i = 0; i < size.X; i++)
	//		{
	//			for (int32 j = 0; j < size.Y; j++)
	//			{
	//				FString key = FString::FromInt(x + i) + FString("/") + FString::FromInt(y + j);
	//				if (GridMap.Contains(key))
	//				{
	//					if (IsValid(GridMap[key]->Occupying))
	//					{
	//						if (GEngine)
	//						{
	//							GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Something is Occupying..."));
	//						}
	//						bCanBuild = false;
	//						break;
	//					}
	//				}
	//				else
	//				{
	//					if (GEngine)
	//					{
	//						GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Not Existed Position"));
	//					}
	//					bCanBuild = false;
	//					break;
	//				}
	//			}


	//			if (bCanBuild == false)
	//			{
	//				break;
	//			}

	//		}

	//		if (bCanBuild)
	//		{
	//			FActorSpawnParameters spawnParam;
	//			ABuilding* building = GetWorld()->SpawnActor<ABuilding>(WantToBuild, SelectedGrid->GetComponentLocation(), FRotator::ZeroRotator, spawnParam);


	//			for (int32 i = 0; i < size.X; i++)
	//			{
	//				for (int32 j = 0; j < size.Y; j++)
	//				{
	//					FString key = FString::FromInt(x + i) + FString("/") + FString::FromInt(y + j);
	//					if (GridMap.Contains(key))
	//					{
	//						GridMap[key]->Occupying = building;
	//						building->OccupyingGrids.Add(GridMap[key]);
	//					}
	//					else
	//					{
	//						if (GEngine)
	//						{
	//							GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Not Existed Position"));
	//						}
	//					}
	//				}
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (GEngine)
	//		{
	//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Not Existed in Grid Map"));
	//		}
	//	}


	//}
	//else
	//{
	//	if (GEngine)
	//	{
	//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("UnValid BuildingClass or GridComponent*"));
	//	}
	//}

}

void AGridManager::DrawAvailableMesh(UGridComponent* InGrid)
{
	if (!IsValid(CurrentSeeGrid) || IsValid(InGrid) && CurrentSeeGrid != InGrid)
	{
		CurrentSeeGrid = InGrid;
		

		if (IsValid(AvailableInstMesh))
		{
			int32 count =  AvailableInstMesh->GetInstanceCount();
			if (count > 0)
			{
				for (int32 i= 0; i < count; i++)
				{
					AvailableInstMesh->RemoveInstance(i);
				}
			}


			FVector location = InGrid->GetRelativeLocation();
			FTransform transform;
			transform.SetLocation(location);

			//UE_LOG(LogTemp, Warning, TEXT("%s"), *transform.ToString());

			AvailableInstMesh->AddInstance(transform);
		}


	}


}

void AGridManager::RemoveAvailableMesh()
{
	CurrentSeeGrid = nullptr;

	if (IsValid(AvailableInstMesh))
	{
		int32 count = AvailableInstMesh->GetInstanceCount();
		if (count > 0)
		{
			for (int32 i = 0; i < count; i++)
			{
				AvailableInstMesh->RemoveInstance(i);
			}
		}
	}

}

