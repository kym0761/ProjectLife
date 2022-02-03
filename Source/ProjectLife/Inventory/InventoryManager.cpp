// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryManager.h"
#include "../ProjectLIfeGameInstance.h"
#include "../Item/ItemPickup.h"

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
	
	//temp.. Player Inventory
	//1,2,3.... Storage Inventory
	for (int32 i = 0; i < 10; i++)
	{
		TryMakeInventorySpace(i);
	}
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
		return;
	}
	else // Add New Inventory.
	{
		UInventory* inventory = NewObject<UInventory>();
		Inventories.Add(Num, inventory);
		for (int i = 0; i < 30; i++)
		{
			inventory->Items.Add(FItemDataSlot());
		}
		//UE_LOG(LogTemp, Warning, TEXT("inventory Made."));
	}
}

bool AInventoryManager::SwapItemBetweenInventory(int32 From, int32 FromSlot, int32 To, int32 ToSlot)
{
	if (!(CheckValidInventory(From) && CheckValidInventory(To)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Valid Inventory"));
		return false;
	}

	if (Inventories[From]->Items.IsValidIndex(FromSlot) && Inventories[To]->Items.IsValidIndex(ToSlot))
	{
		FItemDataSlot i1 = Inventories[From]->Items[FromSlot];
		FItemDataSlot i2 = Inventories[To]->Items[ToSlot];

		if (!Inventories[From]->Items[FromSlot].IsSameItem(Inventories[To]->Items[ToSlot])) //다른 아이템이 들어있는 슬롯이라면, Swap함.
		{
			Inventories[From]->Items[FromSlot] = i2;
			Inventories[To]->Items[ToSlot] = i1;

			return true;
		}
		else //같은 아이템이 존재한다면 join
		{
			UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

			if (IsValid(gameInstance))
			{
				FItemData itemData = gameInstance->GetItemDataFromTable(i1.ItemName); // Get Item Data

				if (itemData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
				{
					i1.Quantity += i2.Quantity;
					i2 = FItemDataSlot();

					Inventories[From]->Items[FromSlot] = i2;
					Inventories[To]->Items[ToSlot] = i1;

					//UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
					return true;
				}
				else //둘이 합쳐서 최대 수량을 초과하면.. "ToSlot"에는 Max Quantity 만큼 들어감 , "FromSlot"에는 나머지가 들어감.
				{
					int32 temp = i1.Quantity + i2.Quantity;
					i1.Quantity = itemData.MaxQuantity;

					temp -= i1.Quantity;
					i2.Quantity = temp;

					Inventories[From]->Items[FromSlot] = i2;
					Inventories[To]->Items[ToSlot] = i1;

					//UE_LOG(LogTemp, Warning, TEXT("join2 Success"));
					return true;
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed"));
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

FItemDataSlot AInventoryManager::AddItemToInventory(FItemDataSlot InData)
{
	//빈 FItemDataSlot을 뱉으면 실패.
	//이름 값이 있으며 Quantity의 값이 0이나 혹은 그 이상일때 성공.
	//값이 음수여도 일단 성공.

	if (Inventories.Contains(PLAYER_INVENTORY))
	{
		if (InData.IsEmpty()) // 빈 정보를 왜 넣음?
		{
			//UE_LOG(LogTemp, Warning, TEXT("?"));
			return FItemDataSlot();
		}
		else
		{
			UProjectLIfeGameInstance* gameinstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

			if (IsValid(gameinstance))
			{
				FItemData itemData = gameinstance->GetItemDataFromTable(InData.ItemName);
				if (itemData.IsEmpty())
				{
					//잘못된 정보는 넣지 않음.
					return FItemDataSlot();
				}

				//!! : 만약 1번이라도 얻게 됐다면, 인벤토리에 반영이 되므로, FItemDataSlot의 빈 값을 내면 안됨.

				FItemDataSlot leftover = InData;
				for (int i = 0; i < Inventories[PLAYER_INVENTORY]->MaxCapacity; i++)
				{
					if (Inventories[PLAYER_INVENTORY]->Items[i].ItemName == leftover.ItemName && Inventories[PLAYER_INVENTORY]->Items[i].Quantity < itemData.MaxQuantity)
					{
						int32 extra = itemData.MaxQuantity - Inventories[PLAYER_INVENTORY]->Items[i].Quantity;
						int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

						Inventories[PLAYER_INVENTORY]->Items[i].Quantity += tempOffset;

						leftover.Quantity -= tempOffset;

						if (leftover.Quantity == 0)
						{
							//남은게 없으면 성공.
							return leftover;
						}
						else if (leftover.Quantity < 0)
						{
							//음수면 문제가 있긴함.
							return leftover;
						}
					}
				}

				//여기까지 왔다면, leftover의 양이 남아있거나, 혹은 같은 슬롯을 찾지 못함.
				//빈 공간 있으면 정보를 넣는다.
				for (int i = 0; i < Inventories[PLAYER_INVENTORY]->MaxCapacity; i++)
				{
					if (Inventories[PLAYER_INVENTORY]->Items[i].IsEmpty())
					{
						SetInventoryItem(0, i, leftover);
						
						leftover.Quantity = 0;
						return leftover;
					}
				}

				//Warning 1 : leftover의 아이템을 약간 얻었는데, 바닥에 떨어진 아이템 처리가 제대로 되지 않음.
				//Warning 2 : 보상을 얻으려 했는데, 보상이 초과되서 남음 or 인벤토리 공간이 없어서 보상을 아예 얻지 못함.
				return leftover;
			}
		}
	}

	return FItemDataSlot();
}

bool AInventoryManager::AddPickupToInventory(AItemPickup* Pickup)
{
	//pickup의 데이터를 인벤토리에 반영하고, 그 후에 제거하기 위해서 필요한 기능.
	//true면 ItemPickup 내부에서 Destroy할 것.

	FItemDataSlot temp = AddItemToInventory(Pickup->ItemDataSlot);

	if (temp.IsEmpty())
	{
		//잘못된 데이터를 전달함.
		//UE_LOG(LogTemp, Warning, TEXT("Invalid Data"));
		return false;
	}
	else
	{
		if (temp.Quantity == 0)
		{
			//UE_LOG(LogTemp, Warning, TEXT("OK, pickup is 0"));
			return true;
		}
		else
		{
			Pickup->ItemDataSlot = temp;
			//UE_LOG(LogTemp, Warning, TEXT("pickup leftover"));
			return false;
		}
	}


	return false;
}
