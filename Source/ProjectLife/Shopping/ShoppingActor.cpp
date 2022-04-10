// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingActor.h"
#include "../Item/Item.h"
#include "Components/BoxComponent.h"
#include "ShoppingWidget.h"
#include "../Base/BasicPlayerController.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"

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

	InitShop();
}

void AShoppingActor::InitShop()
{
	if (IsValid(ShoppingDataTable))
	{
		TArray<FShopItemData*> temp;
		ShoppingDataTable->GetAllRows<FShopItemData>("", temp);

		TArray<FName> names = ShoppingDataTable->GetRowNames();
		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(gameInstance))
		{
			for (FName name : names)
			{
				FItemData itemData = gameInstance->GetItemDataFromTable(name.ToString());
				Items.Add(itemData);
			}
		}
	}
}

// Called every frame
void AShoppingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShoppingActor::Interact_Implementation(APawn* InteractCauser)
{
	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage((int32)FMath::Rand(), 5.0f, FColor::Turquoise, TEXT("Shopping Start"));
	//}

	//InteractorCauser Will be "Player".
	//Make UI For Shopping.
	ABasicPlayerController* playerController = InteractCauser->GetController<ABasicPlayerController>();
	if (IsValid(ShoppingWidgetClass) && IsValid(playerController))
	{
		ShoppingWidgetRef = CreateWidget<UShoppingWidget>(playerController, ShoppingWidgetClass);
		if (IsValid(ShoppingWidgetRef))
		{
			ShoppingWidgetRef->AddToViewport();
			ShoppingWidgetRef->SetPositionInViewport(FVector2D(100, 100));
			ShoppingWidgetRef->InitShoppingWidget(this);

			playerController->bShowMouseCursor = true;
			playerController->SetInputMode(FInputModeUIOnly());

			//flush input : UI가 생성된 뒤 UI Only 모드로 넘어가면 아직 존재하는 input에 반응해 움직이는 것을 방지.
			playerController->FlushPressedKeys();
		}
	}

}

bool AShoppingActor::Transaction(UInventoryComponent* InventoryComponent, int32 Index, int32 Quantity)
{
	if (Quantity == 0)
	{
		return false;
	}

	if (!IsValid(InventoryComponent))
	{
		return false;
	}

	if (!InventoryComponent->CheckInventoryHasSpace())
	{
		return false;
	}

	int totalPrice = Items[Index].ItemPrice * Quantity;
	if (InventoryComponent->CheckEnoughMoney(totalPrice))
	{
		FItemSlotData inData;
		inData.ItemName = Items[Index].Name;
		inData.Quantity = Quantity;

		//TODO : Check that player can buy.
		InventoryComponent->AddItemToInventory(inData);
		InventoryComponent->SpendMoney(totalPrice);
		return true;
	}

	return false;
}
