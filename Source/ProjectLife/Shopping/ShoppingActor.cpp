// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingActor.h"
#include "../Item/Item.h"
#include "Components/BoxComponent.h"
#include "ShoppingWidget.h"
#include "../Base/BasicPlayerController.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryManager.h"

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
		for (FShopItemData* item : temp)
		{
			ShopItems.Add(*item);
		}

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

			ShoppingWidgetRef->ShoppingActorRef = this;
			playerController->bShowMouseCursor = true;
			playerController->SetInputMode(FInputModeUIOnly());

			//flush input : UI가 생성된 뒤 UI Only 모드로 넘어가면 아직 존재하는 input에 반응해 움직이는 것을 방지.
			playerController->FlushPressedKeys();
		}
	}

}

bool AShoppingActor::Transaction(int32 Index, int32 Quantity)
{
	if (Quantity == 0)
	{
		return false;
	}

	//거래를 inventoryManager와 해야함. 만약 거래를 못한다면 월드에 inventoryManager가 없을 수도 있음.
	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		//공간없으면 거래 중지
		//Warning. 인벤토리의 슬롯에 아이템이 꽉 찼을 수는 있지만, 여분을 stack할 아이템 슬롯이 있을 수는 있음.
		if (!inventoryManager->CheckPlayerInventoryHasSpace())
		{
			return false;
		}

		int totalPrice = Items[Index].ItemPrice * Quantity;
		
		//플레이어가 적절한 돈을 가지고 있다면 거래.
		if (inventoryManager->Money >= totalPrice)
		{
			FItemDataSlot inData;
			inData.ItemName = Items[Index].Name;
			inData.Quantity = Quantity;

			//TODO : Check that player can buy.
			inventoryManager->AddItemToInventory(inData);
			inventoryManager->SpendMoney(totalPrice);
			return true;			
		}
	}

	return false;
}
