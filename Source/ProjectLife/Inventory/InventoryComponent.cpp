// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	for (int32 i = 0; i < 30; i++)
	{
		Items.Add(FItemDataSlot());
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
	FItemDataSlot slot;
	for (int32 i = 0; i < Num; i++)
	{
		Items.Add(slot);
	}
}

bool UInventoryComponent::SwapItemBetweenInventory(UInventoryComponent* From, int32 FromSlot, UInventoryComponent* To, int32 ToSlot)
{
	if (!(IsValid(From) && IsValid(To)))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not Valid Inventory"));
		return false;
	}

	if (From->Items.IsValidIndex(FromSlot) && To->Items.IsValidIndex(ToSlot))
	{
		FItemDataSlot i1 = From->Items[FromSlot];
		FItemDataSlot i2 = To->Items[ToSlot];

		if (!From->Items[FromSlot].IsSameItem(To->Items[ToSlot])) //다른 아이템이 들어있는 슬롯이라면, Swap함.
		{
			From->Items[FromSlot] = i2;
			To->Items[ToSlot] = i1;

			return true;
		}
		else  //같은 아이템이 존재한다면 join
		{
			//문제가 있을 수 있음. 임시로 뗌빵.
			UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

			if (!IsValid(gameInstance))
			{
				UE_LOG(LogTemp, Warning, TEXT("Access GameInstance Failed"));
				return false;
			}

			FItemData itemData = gameInstance->GetItemDataFromTable(i1.ItemName); // Get Item Data

			if (itemData.MaxQuantity >= i1.Quantity + i2.Quantity) //ToSlot 갯수랑 FromSlot 갯수의 합이 한 슬롯에 들어갈 정도로 충분하면.. "ToSlot"에 아이템이 전부 들어감. "FromSlot"은 빈 슬롯이 됨.
			{
				i1.Quantity += i2.Quantity;
				i2 = FItemDataSlot();

				From->Items[FromSlot] = i2;
				To->Items[ToSlot] = i1;

				//UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
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
				return true;
			}
		}
	}

	return false;
}

FItemDataSlot UInventoryComponent::GetInventoryItem(int32 SlotNumber)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		//성공시 어떤 값?
		return Items[SlotNumber];
	}

	//실패시 빈값.
	return FItemDataSlot();
}

bool UInventoryComponent::SetInventoryItem(int32 SlotNumber, FItemDataSlot InData)
{
	if (Items.IsValidIndex(SlotNumber))
	{
		Items[SlotNumber] = InData;
		return true;
	}

	return false;
}

int32 UInventoryComponent::AddItemToInventory(FItemDataSlot InData)
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
	FItemDataSlot leftover = InData;
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
				return 0;
			}
			else if (leftover.Quantity < 0)
			{
				//음수면 문제가 있긴함. 다만, 인벤토리에 반영이 됐으므로 일단 0으로 취급
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
			return 0;
		}
	}
	//Warning 1 : leftover의 아이템을 약간 얻었는데, 바닥에 떨어진 아이템 처리가 제대로 되지 않음.
	//Warning 2 : 보상을 얻으려 했는데, 보상이 초과되서 남음 or 인벤토리 공간이 없어서 보상을 아예 얻지 못함.
	return leftover.Quantity;


}

bool UInventoryComponent::CheckPlayerInventoryHasSpace()
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		FItemDataSlot item = Items[i];
		if (item.IsEmpty())
		{
			return true;
		}
	}

	return false;
}

