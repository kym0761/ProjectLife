// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageBox.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Blueprint/UserWidget.h"
#include "StorageWidget.h"
#include "../Base/BasicPlayerController.h"

AStorageBox::AStorageBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StorageMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StorageMesh);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(StorageMesh);
	Sphere->SetCollisionProfileName(FName("OverlapAll"));
	Sphere->SetSphereRadius(128.0f);

	bOpen = false;

}

void AStorageBox::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentEndOverlap.AddDynamic(this, &AStorageBox::EndOverlap);

	if (StorageNumber == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : Storage Number is equal with Playerinventory. It's wrong."));
	}
}

void AStorageBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStorageBox::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if Player's StorageUI is ON, Remove that.

	if (bOpen)
	{
		APawn* player = Cast<APawn>(OtherActor);
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
