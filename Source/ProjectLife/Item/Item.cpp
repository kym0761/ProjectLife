// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
#include "../Base/BasicWeapon.h"
// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SetRootComponent(Sphere);
	Sphere->InitSphereRadius(64.0f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);


}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	UItemData* data = ItemDataTest.GetDefaultObject();
	if (data)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.0f, FColor::Black,data->Name);
		}
	}
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
		bool bSucceeded = player->Inventory->AddItemToInventory(ItemData);
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
	switch (ItemData.ItemType)
	{
	case EItemType::Consumption:
		UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Consumption"));
		break;
	case EItemType::Equipment:
		UE_LOG(LogTemp, Warning, TEXT("C++ UseItem(), Type is Equipment"));
		if (ItemData.WeaponClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Class Name : %s"), *ItemData.WeaponClass.GetDefaultObject()->ItemData.Name);
		}
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

