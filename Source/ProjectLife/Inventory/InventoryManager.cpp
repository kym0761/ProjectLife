// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "../ProjectLIfeGameInstance.h"

UInventory::UInventory()
{
	MaxCapacity = 30;
}

// Sets default values
AInventoryManager::AInventoryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Money = 10000;
}

// Called when the game starts or when spawned
void AInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInventoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AInventoryManager::CheckValidInventory(int32 InventoryNumber)
{
	bool temp = Inventories.Contains(InventoryNumber);

	if (temp == true)
	{
		return true;
	}

	return false;
}

bool AInventoryManager::CheckInventoryHasSpace(int32 InventoryNumber)
{
	bool bHasSpace = false;
	
	if (!CheckValidInventory(InventoryNumber))
	{
		return false;
	}

	UInventory* inventory = Inventories[InventoryNumber];

	if (IsValid(inventory))
	{
		for (int32 i = 0; i < inventory->Items.Num(); i++)
		{
			if (inventory->Items[i].Quantity == 0)
			{
				bHasSpace = true;
				break;
			}
		}
	}

	return bHasSpace;
}

int32 AInventoryManager::GetCurrentMoney()
{
	return Money;
}

bool AInventoryManager::SpendMoney(int32 OutMoney)
{
	if (Money < OutMoney)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Can't Spend Money, Demand is Over the In-Hand"));
		}

		return false;
	}
	else
	{
		Money = FMath::Clamp(Money - OutMoney, 0, TNumericLimits<int32>::Max());
		return true;
	}
}

void AInventoryManager::GainMoney(int32 InMoney)
{
	Money = FMath::Clamp(Money + InMoney, 0, TNumericLimits<int32>::Max());

	if (Money == TNumericLimits<int32>::Max())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Warning! Your Money is Full."));
		}
	}

}

bool AInventoryManager::CheckEnoughMoney(int32 ToCompare)
{
	if (Money >= ToCompare)
	{
		return true;
	}

	return false;
}

void AInventoryManager::TryMakeInventorySpace(int32 Num)
{
	bool temp = CheckValidInventory(Num);

	if (temp)
	{
		//Do Nothing..?
	}
	else // Add New Inventory.
	{
		UInventory * inventory = NewObject<UInventory>();
		Inventories.Add(Num, inventory);
	}
}

bool AInventoryManager::SwapItemBetweenInventory(int32 From, int32 FromSlot, int32 To, int32 ToSlot)
{
	if (!(CheckValidInventory(From) && CheckValidInventory(To)))
	{
		return false;
	}

	if (Inventories[From]->Items.IsValidIndex(FromSlot) && Inventories[To]->Items.IsValidIndex(ToSlot))
	{
		FItemDataSlot i1 = Inventories[From]->Items[FromSlot];
		FItemDataSlot i2 = Inventories[To]->Items[ToSlot];

		if (!Inventories[From]->Items[FromSlot].IsSameItem(Inventories[To]->Items[ToSlot])) //swap
		{
			Inventories[From]->Items[FromSlot] = i2;
			Inventories[To]->Items[ToSlot] = i1;

			return true;
		}
		else //join
		{
			UProjectLIfeGameInstance* gameinstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

			if (IsValid(gameinstance))
			{
				FItemData itemData = gameinstance->GetItemDataFromTable(i1.ItemName); // Get Item Data

				if (itemData.MaxQuantity >= i1.Quantity + i2.Quantity) //enough.. All Item Will In ToSlot
				{
					i1.Quantity += i2.Quantity;
					i2 = FItemDataSlot();

					Inventories[From]->Items[FromSlot] = i2;
					Inventories[To]->Items[ToSlot] = i1;

					UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
					return true;
				}
				else //Exceed Max Quantity. Max Quantity will be In "ToSlot", And Leftover will be in "FromSlot".
				{
					int32 temp = i1.Quantity + i2.Quantity;
					i1.Quantity = itemData.MaxQuantity;

					temp -= i1.Quantity;
					i2.Quantity = temp;

					Inventories[From]->Items[FromSlot] = i2;
					Inventories[To]->Items[ToSlot] = i1;

					UE_LOG(LogTemp, Warning, TEXT("join2 Success"));
					return true;
				}
			}
		}
	}

	return false;
}

FItemDataSlot AInventoryManager::GetInventoryItem(int32 InventoryNumber, int32 SlotNumber)
{
	if (Inventories.Contains(InventoryNumber))
	{
		if (Inventories[InventoryNumber]->Items.IsValidIndex(SlotNumber))
		{
			return Inventories[InventoryNumber]->Items[SlotNumber];
		}
	}

	return FItemDataSlot();
}

bool AInventoryManager::SetInventoryItem(int32 InventoryNumber, int32 SlotNumber, FItemDataSlot InData)
{
	if (Inventories.Contains(InventoryNumber))
	{
		if (Inventories[InventoryNumber]->Items.IsValidIndex(SlotNumber))
		{
			Inventories[InventoryNumber]->Items[SlotNumber] = InData;
			return true;
		}

	}
	return false;
}

bool AInventoryManager::AddItemToInventory(FItemDataSlot InData)
{
	if (Inventories.Contains(PLAYER_INVENTORY))
	{
		if (InData.IsEmpty()) // 빈 정보를 왜 넣음?
		{
			return false;
		}
		else
		{
			if (Inventories[PLAYER_INVENTORY]->Items.Num() < Inventories[PLAYER_INVENTORY]->MaxCapacity)
			{
				// 공간 있으면 정보를 넣는다.
				Inventories[PLAYER_INVENTORY]->Items.Add(InData);
				return true;
			}
		}
	}

	return false;
}
