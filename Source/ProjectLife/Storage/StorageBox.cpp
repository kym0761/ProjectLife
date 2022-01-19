// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageBox.h"
#include "Blueprint/UserWidget.h"
#include "StorageWidget.h"
#include "../Base/BasicCharacter.h"
#include "Components/SphereComponent.h"
#include "../Base/BasicPlayerController.h"

AStorageBox::AStorageBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	//Inventory->InventoryCapacity = 20;

	bOpen = false;

}

void AStorageBox::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AStorageBox::EndOverlap);
}

void AStorageBox::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if Player's StorageUI is ON, Remove that.

	if (bOpen)
	{
		ABasicCharacter* player = Cast<ABasicCharacter>(OtherActor);
		if (player)
		{
			ABasicPlayerController* playerController = player->GetController<ABasicPlayerController>();
			if (playerController)
			{
				playerController->ToggleStorageWidget(this);
				bOpen = false;
			}
		}
	}

}

void AStorageBox::Interact_Implementation(APawn* InteractCauser)
{
	//Add To Viewport Storage UI.

	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();
	if (playerController)
	{
		playerController->ToggleStorageWidget(this);

		if (bOpen)
		{
			bOpen = false;
		}
		else
		{
			bOpen = true;
		}
	}

}
