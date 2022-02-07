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

			//flush input : UI�� ������ �� UI Only ���� �Ѿ�� ���� �����ϴ� input�� ������ �����̴� ���� ����.
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

	//�ŷ��� inventoryManager�� �ؾ���. ���� �ŷ��� ���Ѵٸ� ���忡 inventoryManager�� ���� ���� ����.
	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		//���������� �ŷ� ����
		//Warning. �κ��丮�� ���Կ� �������� �� á�� ���� ������, ������ stack�� ������ ������ ���� ���� ����.
		if (!inventoryManager->CheckPlayerInventoryHasSpace())
		{
			return false;
		}

		int totalPrice = Items[Index].ItemPrice * Quantity;
		
		//�÷��̾ ������ ���� ������ �ִٸ� �ŷ�.
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
