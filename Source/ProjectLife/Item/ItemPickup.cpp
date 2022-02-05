// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickup.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicCharacter.h"
#include "../Base/BasicPlayerController.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryManager.h"

// Sets default values
AItemPickup::AItemPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->InitBoxExtent(FVector(32.0f));
	Box->SetCollisionProfileName(TEXT("Item"));
	//Collision->SetVisibility(false);
	Box->ShapeColor = FColor::Black;
	Box->SetSimulatePhysics(true);
	Box->GetBodyInstance()->bLockXRotation = true;
	Box->GetBodyInstance()->bLockYRotation = true;
	Box->GetBodyInstance()->bLockZRotation = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->InitSphereRadius(64.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AItemPickup::BeginPlay()
{
	Super::BeginPlay();
	
	//item 정보가 없을 시에는 랜덤 정보를 가져와서 템을 생성함.
	if (ItemDataSlot.IsEmpty())
	{
		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(gameInstance))
		{
			TArray<FName> names = gameInstance->ItemDataTable->GetRowNames();
			
			int randIndex = FMath::RandRange(0, names.Num() - 1);

			FItemData itemData = gameInstance->GetItemDataFromTable(names[randIndex].ToString());

			ItemDataSlot.ItemName = itemData.Name;
			ItemDataSlot.Quantity = 1;

			Mesh->SetStaticMesh(itemData.ItemMesh);
		}
	}

}

// Called every frame
void AItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemPickup::Interact_Implementation(APawn* InteractCauser)
{	
	AInventoryManager* inventoryManager
	= Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	ABasicCharacter* player = Cast<ABasicCharacter>(InteractCauser);

	if (IsValid(inventoryManager) && IsValid(player))
	{
		//Add to player's Inventory.
		bool bSucceeded = inventoryManager->AddPickupToInventory(this);
		//Succeeded, Update UI & Delete Item Actor.
		
		ABasicPlayerController* playerController = player->GetController<ABasicPlayerController>();
		if (playerController)
		{
			playerController->UpdateInventory();
		}

		if (bSucceeded)
		{
			Destroy();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AItemPickup::Interact_Implementation() X"));
	}

}

//bool AItemPickup::UseItem_Implementation()
//{
//
//	FItemData itemdata;
//
//	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//	if (IsValid(gameInstance))
//	{
//		itemdata = gameInstance->GetItemDataFromTable(ItemName);
//
//		switch (itemdata.ItemType)
//		{
//		case EItemType::Consumption:
//			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Consumption"));
//			break;
//		case EItemType::Equipment:
//			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Equipment"));
//			break;
//		case EItemType::Resource:
//			UE_LOG(LogTemp, Warning, TEXT("Resource Item Will not Need Use Item function Maybe..?"));
//			break;
//		default:
//			UE_LOG(LogTemp, Warning, TEXT("I don't Know.."));
//			break;
//		}
//
//		return true;
//	}
//
//	return false;
//}

