// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingActor.h"
#include "../Item/Item.h"
#include "Components/BoxComponent.h"
#include "ShoppingWidgetBase.h"
#include "../Base/BasicPlayerController.h"

// Sets default values
AShoppingActor::AShoppingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShoppingCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ShoppingCollision"));
	ShoppingCollision->InitBoxExtent(FVector(64.0f));

	ShoppingWidgetRef = nullptr;
}

// Called when the game starts or when spawned
void AShoppingActor::BeginPlay()
{
	Super::BeginPlay();
	
	//if (GEngine)
	//{
	//	for (int32 i = 0; i < Items.Num(); i++)
	//	{
	//		if (Items[i])
	//		{
	//			FString temp = Items[i].GetDefaultObject()->ItemData.Name;
	//			GEngine->AddOnScreenDebugMessage((int32)FMath::Rand(), 5.0f, FColor::Turquoise, temp);
	//		}
	//	}
	//}
}

// Called every frame
void AShoppingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShoppingActor::Interact_Implementation(APawn* InteractCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage((int32)FMath::Rand(), 5.0f, FColor::Turquoise, TEXT("Shopping Start"));
	}

	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();

	if (ShoppingWidgetClass && playerController)
	{
		ShoppingWidgetRef = CreateWidget<UShoppingWidgetBase>(playerController, ShoppingWidgetClass);
		if (ShoppingWidgetRef)
		{
			ShoppingWidgetRef->AddToViewport();
			ShoppingWidgetRef->SetPositionInViewport(FVector2D(100, 100));


			ShoppingWidgetRef->InitShoppingWidget(this);

			ShoppingWidgetRef->ShoppingActorRef = this;
			playerController->bShowMouseCursor = true;
			playerController->SetInputMode(FInputModeUIOnly());
			//InteractCauser->DisableInput(nullptr);
		}
	}

}