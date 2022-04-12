// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

#include "../Item/Item.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	//Disabled
	PrimaryComponentTick.bCanEverTick = false;

	for (int32 i = 0; i < 30; i++)
	{
		Items.Add(FItemSlotData());
	}

	//temp
	Money = 10000;
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Disabled
}

bool UInventoryComponent::CheckInventoryHasSpace()
{
	bool bHasSpace = false;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Quantity == 0)
		{
			bHasSpace = true;
			break;
		}
	}

	return bHasSpace;
}

bool UInventoryComponent::SpendMoney(int32 Spend)
{
	if (Money < Spend)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Can't Spend Money, Demand is Over the In-Hand"));
		}

		return false;
	}
	else
	{
		Money = FMath::Clamp(Money - Spend, 0, TNumericLimits<int32>::Max());
		return true;
	}
}

void UInventoryComponent::GainMoney(int32 Gain)
{
	Money = FMath::Clamp(Money + Gain, 0, TNumericLimits<int32>::Max());

	if (Money == TNumericLimits<int32>::Max())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(256, 5.0f, FColor::Silver, TEXT("Warning! Your Money is Full."));
		}
	}
}

bool UInventoryComponent::CheckEnoughMoney(int32 ToCompare)
{
	if (Money >= ToCompare)
	{
		return true;
	}

	return false;
}

void UInventoryComponent::TryMakeInventorySpace(int32 Num)
{
	//빈 아이템 슬롯
	FItemSlotData slot;
	for (int32 i = 0; i < Num; i++)
	{
		Items.Add(slot);
	}
}

bool UInventoryComponent::SwapItemBetweenInventory(UInventoryComponent* From, int32 FromSlot, UInventoryComponent* To, int32 ToSlot)
{
	//static Function에선 GetWorld()를 바로 할 수 없다.
	//GEngine을 먼저 불러와서 Valid 체크를 한 뒤에 GetWorld를 확인해야함.

	if (!(IsValid(From) && IsValid(To) && IsValid(GEngine)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Valid Inventory"));
		return false;
	}

	if (From->Items.IsValidIndex(FromSlot) && To->Items.IsValidIndex(ToSlot))
	{
		FItemSlotData i1 = From->Items[FromSlot];
		FItemSlotData i2 = To->Items[ToSlot];

		if (!From->Items[FromSlot].IsSameItem(To->Items[ToSlot])) //다른 아이템이 들어있는 슬롯이라면, Swap함.
		{
			From->Items[FromSlot] = i2;
			To->Items[ToSlot] = i1;

			From->OnInventoryDataChanged.Broadcast();
			To->OnInventoryDataChanged.Broadcast();
			return true;
		}
		else  //같은 아이템이 존재한다면 join
		{
			//static Function이므로 World를 GEngine에서 받아와야함.
			UWorld* world = GEngine->GetWorldFromContextObject(From, EGetWorldErrorMode::LogAndReturnNull);

			if (!IsValid(world))
			{
				//world null?
				return false;
			}

			UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(world));

			if (!IsValid(gameInstance))
			{
				UE_LOG(LogTemp, Warning, TEXT("Access GameInstance Failed"));
				return false;
			}

			FItemData itemData = gameInstance->GetItemDataFromTable(i1.ItemName); // Get Item Data

			if (itemData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot 갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
			{
				i1.Quantity += i2.Quantity;
				i2 = FItemSlotData();

				From->Items[FromSlot] = i2;
				To->Items[ToSlot] = i1;

				//UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
				From->OnInventoryDataChanged.Broadcast();
				To->OnInventoryDataChanged.Broadcast();
				return true;
			}
			else //둘이 합쳐서 최대 수량을 초과하면.. "ToSlot"에는 Max Quantity 만큼 들어감 , "FromSlot"에는 나머지가 들어감.
			{
				int32 temp = i1.Quantity + i2.Quantity;
				i1.Quantity = itemData.MaxQuantity;

				temp -= i1.Quantity;
				i2.Quantity = temp;

				From->Items[FromSlot] = i2;
				To->Items[ToSlot] = i1;

				//UE_LOG(LogTemp, Warning, TEXT("join2 Success"));
				From->OnInventoryDataChanged.Broadcast();
				To->OnInventoryDataChanged.Broadcast();
				return true;
			}
		}
	}

	return false;
}

FItemSlotData UInventoryComponent::GetInventoryItem(int32 SlotNumber)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		//성공시 내용이 존재하는 어떤 값?
		return Items[SlotNumber];
	}

	//실패시 빈값.
	return FItemSlotData();
}

bool UInventoryComponent::SetInventoryItem(int32 SlotNumber, FItemSlotData InData)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		Items[SlotNumber] = InData;
		OnInventoryDataChanged.Broadcast();
		return true;
	}

	return false;
}

int32 UInventoryComponent::AddItemToInventory(FItemSlotData InData)
{
	// -1 이하 실패, 0 --> 성공적으로 다 들어감, 1 이상--> 남음.

	if (InData.IsEmpty())
	{
		// 빈 정보는 넣지 않음.
		return -1;
	}

	UProjectLIfeGameInstance* gameinstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (!IsValid(gameinstance))
	{
		return -1;
	}

	FItemData itemData = gameinstance->GetItemDataFromTable(InData.ItemName);
	if (itemData.IsEmpty())
	{
		//잘못된 정보. 넣지 않음.
		return -1;
	}


	//!! : 만약 한 번이라도 얻게 됐다면, 인벤토리에 반영이 되므로 FItemDataSlot의 빈 값을 내면 안됨.
	FItemSlotData leftover = InData;
	for (int i = 0; i < Items.Num(); i++)
	{
		//인벤토리에서 넣고 싶은 아이템과 같은 아이템을 슬롯을 찾고, 아직 꽉 찬 슬롯이 아니라면 내용물을 채운다.
		if (Items[i].ItemName == leftover.ItemName && Items[i].Quantity < itemData.MaxQuantity)
		{
			int32 extra = itemData.MaxQuantity - Items[i].Quantity;
			int32 tempOffset = FMath::Clamp(leftover.Quantity, 0, extra);

			Items[i].Quantity += tempOffset;

			leftover.Quantity -= tempOffset;

			if (leftover.Quantity == 0)
			{
				//남은게 없으면 성공.
				OnInventoryDataChanged.Broadcast();
				return 0;
			}
			else if (leftover.Quantity < 0)
			{
				//음수면 문제가 있긴함. 다만, 인벤토리에 반영이 됐으므로 일단 0으로 취급
				OnInventoryDataChanged.Broadcast();
				return 0;
			}
		}
	}
	//여기까지 왔다면, leftover의 양이 남아있거나, 혹은 같은 슬롯을 찾지 못함.
	//빈 공간 있으면 정보를 넣는다.
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].IsEmpty())
		{
			SetInventoryItem(i, leftover);
			OnInventoryDataChanged.Broadcast();
			return 0;
		}
	}
	//Warning 1 : leftover의 아이템을 약간 얻었는데, 바닥에 떨어진 아이템 처리가 제대로 되지 않음.
	//Warning 2 : 보상을 얻으려 했는데, 보상이 초과되서 남음 or 인벤토리 공간이 없어서 보상을 아예 얻지 못함.
	OnInventoryDataChanged.Broadcast();
	return leftover.Quantity;


}

bool UInventoryComponent::CheckPlayerInventoryHasSpace()
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		FItemSlotData item = Items[i];
		if (item.IsEmpty())
		{
			return true;
		}
	}

	return false;
}

bool UInventoryComponent::UseItemInInventory(int32 ItemIndex)
{
	//TODO : Item 종류에 따라 아이템 갯수를 내리거나 등등의 기능 필요함.

	if (Items.IsValidIndex(ItemIndex))
	{
		UProjectLIfeGameInstance* gameinstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(gameinstance))
		{
			FItemData itemData = gameinstance->GetItemDataFromTable(Items[ItemIndex].ItemName);
			AItem* item = GetWorld()->SpawnActor<AItem>(itemData.ItemClass);
			if (IsValid(item))
			{
				item->SetOwner(GetOwner());
				item->UseItem();
				OnInventoryDataChanged.Broadcast();
				return true;
			}
		}

	}

	return false;
}

bool UInventoryComponent::CheckItemInInventory(FString ItemName, int32 Quantity)
{
	int32 t_Quantity = Quantity;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		//아이템 찾아서 필요한 양을 찾아서 줄임. 그리고 t_Quantity가 <=0이 된다면 아이템이 충분히 있으니 종료.
		if (ItemName == Items[i].ItemName)
		{
			t_Quantity -= Items[i].Quantity;
			if (t_Quantity <= 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool UInventoryComponent::UseItemsInInventory(FString ItemName, int32 Quantity)
{
	//아마 이 함수를 사용하기 전에 한번 체크를 해볼 것 같지만, 사용 기능 안에서도 한번 더 체크함.
	bool b1 = CheckItemInInventory(ItemName, Quantity);
	if (b1 == false)
	{
		return false;
	}

	int32 t_Quantity = Quantity;

	for (int32 i = 0; i < Items.Num(); i++)
	{
		
		if (ItemName == Items[i].ItemName)
		{
			int32 i_Quantity = Items[i].Quantity;

			if (i_Quantity == t_Quantity)
			{
				//값이 같다면 둘다 0값을 넣어줌.
				t_Quantity = 0;
				Items[i] = FItemSlotData();
			}
			else if (i_Quantity > t_Quantity)
			{
				//인벤토리 슬롯에 있는 양만큼 사용하고 남은 값을 기존 인벤토리 슬롯에 넣어줌
				int32 temp = i_Quantity - t_Quantity;
				t_Quantity = 0;
				Items[i].Quantity = temp;
			}
			else //i_Quantity < t_Quantity
			{
				//인벤토리 슬롯의 양이 필요한 양보다 적으면, 필요한 양을 깎고, 슬롯에는 빈값을 넣는다.
				t_Quantity -= i_Quantity;
				Items[i] = FItemSlotData();
			}

			//필요한 양을 전부 깎았으면 종료			
			if (t_Quantity <= 0)
			{
				OnInventoryDataChanged.Broadcast();
				return true;
			}
		}
	}

	//사실 위 루프가 실행되는 것은 인벤토리에 이미 아이템이 있을 것을 가정했을 때만 작동하므로, 여기까지 오지 않을 것임.
	return false;
}

int32 UInventoryComponent::GetMoney() const
{
	return Money;
}

void UInventoryComponent::SetMoney(int32 InVal)
{
	Money = InVal;
}

TArray<FItemSlotData> UInventoryComponent::GetItems() const
{
	return Items;
}

void UInventoryComponent::SetItems(TArray<FItemSlotData> InVal)
{
	Items = InVal;
}

