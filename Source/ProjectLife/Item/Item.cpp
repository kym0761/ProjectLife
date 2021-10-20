// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
#include "../Base/BasicWeapon.h"
// Sets default values

#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

AItem::AItem()
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
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::Interact_Implementation(APawn* InteractCauser)
{
	ABasicCharacter* player = Cast<ABasicCharacter>(InteractCauser);
	
	if (player)
	{
		bool bSucceeded = player->Inventory->AddItemToInventory(ItemName, Quantity);
		//Add Succeeded, Update UI & Delete Item Actor.
		if (bSucceeded)
		{
			ABasicPlayerController* playerController = player->GetController<ABasicPlayerController>();
			if (playerController)
			{
				playerController->UpdateInventory();
			}

			Destroy();
		}
	}
	
}

bool AItem::UseItem_Implementation()
{
	FItemData itemdata;
	
	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (IsValid(gameInstance))
	{
		itemdata = gameInstance->GetItemDataFromTable(ItemName);
	
		switch (itemdata.ItemType)
		{
		case EItemType::Consumption:
			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Consumption"));
			break;
		case EItemType::Equipment:
			UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Equipment"));
			break;
		case EItemType::Resource:
			UE_LOG(LogTemp, Warning, TEXT("Resource Item Will not Need Use Item function Maybe..?"));
			break;
		default:
			UE_LOG(LogTemp, Warning, TEXT("I don't Know.."));
			break;
		}

		return true;
	}

	return false;
}

