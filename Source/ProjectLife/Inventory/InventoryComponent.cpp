// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"
#include "../Item/Item.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	//InitInventory();

}

//void UInventoryComponent::InitInventory()
//{
//	for (int32 i = 0; i < InventoryCapacity; i++)
//	{
//		//Must Init. or You'll Get Error..
//		FItemDataSlot itemDataSlot;
//		itemDataSlot.Quantity = 0;
//		InventoryArray.Add(itemDataSlot);
//	}
//}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

//bool UInventoryComponent::CheckInventoryHasSpace()
//{
//	bool bHasSpace = false;
//	for (int32 i = 0; i < InventoryArray.Num(); i++)
//	{
//		if (InventoryArray[i].Quantity == 0)
//		{
//			bHasSpace = true;
//			break;
//		}
//	}
//
//	return bHasSpace;
//}
//
//bool UInventoryComponent::AddItemToInventory(FItemDataSlot ItemDataSlot)
//{
//	//check Array Has Space
//	bool bHasSpace = false;
//
//	bHasSpace = CheckInventoryHasSpace();
//
//	if (ItemDataSlot.Quantity == 0)
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("Item Quantity is 0. Impossible"));
//		return false;
//	}
//
//	FItemData itemData = ItemDataSlot.ItemData;
//
//	//UE_LOG(LogTemp, Warning, TEXT("%s"), *itemData.Name);
//
//	if (itemData.bIsStackable && itemData.MaxQuantity < ItemDataSlot.Quantity)
//	{
//		//UE_LOG(LogTemp, Warning, TEXT("Item Quantity which Over the MaxQuantity is Impossible. so, Item Quantity will be set to MaxQuantity."));
//		ItemDataSlot.Quantity = itemData.MaxQuantity;
//	}
//
//	if (itemData.bIsStackable)
//	{
//		//Add Quantity of an identical item
//		for (int32 i = 0; i < InventoryArray.Num(); i++)
//		{
//			if (InventoryArray[i].ItemData.ItemClass == itemData.ItemClass)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("%s"), *itemData.Name);
//				UE_LOG(LogTemp, Warning, TEXT("%s"), *InventoryArray[i].ItemData.Name);
//
//				if (InventoryArray[i].Quantity + ItemDataSlot.Quantity <= InventoryArray[i].ItemData.MaxQuantity) // check enough for Max Quantity
//				{
//					InventoryArray[i].Quantity += ItemDataSlot.Quantity;
//					return true;
//				}
//			}
//		}
//
//		//if loop ended, there is no identical Item OR the Identical Item Slot is Full. so, Use Empty Inventory Space.
//		if (bHasSpace)
//		{
//			for (int32 i = 0; i < InventoryArray.Num(); i++)
//			{
//				//Identical Item
//				if (InventoryArray[i].ItemData.ItemClass == itemData.ItemClass)
//				{
//					//check excceed
//					if (InventoryArray[i].Quantity + ItemDataSlot.Quantity > InventoryArray[i].ItemData.MaxQuantity)
//					{
//						int32 temp = InventoryArray[i].Quantity + ItemDataSlot.Quantity;
//						InventoryArray[i].Quantity = InventoryArray[i].ItemData.MaxQuantity;
//						ItemDataSlot.Quantity = temp - InventoryArray[i].Quantity;
//						break; //temp Quantity won't excceed MaxQuantity. so, go to the Next Procedure.
//					}
//					else// if not excceed, join and End Function.
//					{
//						InventoryArray[i].Quantity += ItemDataSlot.Quantity;
//						return true;
//					}
//				}
//
//			}
//
//			//if there is LeftOver, just Add in Empty Space.
//			for (int32 i = 0; i < InventoryArray.Num(); i++)
//			{
//				if (InventoryArray[i].Quantity == 0)
//				{
//					InventoryArray[i] = ItemDataSlot;
//					return true;
//				}
//			}
//		}
//	}
//	else // Can't Stackable Item. - etc)Equipment, Accessory.. - this will be Just Assigned in Empty Space.
//	{
//		if (bHasSpace)
//		{
//			for (int32 i = 0; i < InventoryArray.Num(); i++)
//			{
//				if (InventoryArray[i].Quantity == 0)
//				{
//					InventoryArray[i] = ItemDataSlot;
//					return true;
//				}
//			}
//		}
//	}
//
//	//UE_LOG(LogTemp, Warning, TEXT("Add to Inventory Failed."));
//	////there is no Enough Space to Pick it up.
//	return false;
//}
//
//bool UInventoryComponent::AddItemToInventory(FString ItemName, int32 Quantity)
//{
//	// add item data from gameinstance's data table.
//
//	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//	
//	if (IsValid(gameInstance))
//	{
//		FItemData itemData = gameInstance->GetItemDataFromTable(ItemName);
//
//		FItemDataSlot itemDataSlot;
//		itemDataSlot.ItemData = itemData;
//		itemDataSlot.Quantity = Quantity;
//
//		bool bSucceed = AddItemToInventory(itemDataSlot);
//		return bSucceed;
//	}
//
//
//	return false;
//}
//
//void UInventoryComponent::PopItemFromInventory(int32 Index)
//{
//	if (InventoryArray.IsValidIndex(Index))
//	{
//		if (InventoryArray[Index].ItemData.bIsStackable) // Stackable Item.
//		{
//			if (InventoryArray[Index].Quantity > 1) // Decrease Item Number
//			{
//				InventoryArray[Index].Quantity--;
//			}
//			else if (InventoryArray[Index].Quantity == 1) //Delete and Reset
//			{
//				InventoryArray[Index] = FItemDataSlot();
//			}
//		}
//		else // not Stackable item will be just Deleted and Reset.
//		{
//			InventoryArray[Index] = FItemDataSlot();
//		}
//
//	}
//}
//
//bool UInventoryComponent::SwapInventoryItem(int32 CurrentInventoryIndex, UInventoryComponent* OtherInventory, int32 OtherInventoryIndex)
//{
//	if (IsValid(OtherInventory))
//	{
//
//		if (InventoryArray[CurrentInventoryIndex].ItemData.ItemClass == OtherInventory->InventoryArray[OtherInventoryIndex].ItemData.ItemClass) // join.
//		{
//			if (InventoryArray[CurrentInventoryIndex].ItemData.MaxQuantity
//				>= InventoryArray[CurrentInventoryIndex].Quantity + OtherInventory->InventoryArray[OtherInventoryIndex].Quantity) //enough Quantity for join
//			{
//				InventoryArray[CurrentInventoryIndex].Quantity += OtherInventory->InventoryArray[OtherInventoryIndex].Quantity;
//				OtherInventory->InventoryArray[OtherInventoryIndex] = FItemDataSlot();
//				UE_LOG(LogTemp, Warning, TEXT("join1 Success"));
//				return true;
//			}
//			else //Exceed Max Quantity.
//			{
//				int32 temp = InventoryArray[CurrentInventoryIndex].Quantity + OtherInventory->InventoryArray[OtherInventoryIndex].Quantity;
//				InventoryArray[CurrentInventoryIndex].Quantity = InventoryArray[CurrentInventoryIndex].ItemData.MaxQuantity;
//				temp -= InventoryArray[CurrentInventoryIndex].Quantity;
//				OtherInventory->InventoryArray[OtherInventoryIndex].Quantity = temp;
//				UE_LOG(LogTemp, Warning, TEXT("join2 Success"));
//				return true;
//			}
//		}
//		else //swap
//		{
//			FItemDataSlot temp = OtherInventory->InventoryArray[OtherInventoryIndex];
//			OtherInventory->InventoryArray[OtherInventoryIndex] = InventoryArray[CurrentInventoryIndex];
//			InventoryArray[CurrentInventoryIndex] = temp;
//			UE_LOG(LogTemp, Warning, TEXT("Swap Success"));
//			return true;
//		}
//	}
//	UE_LOG(LogTemp, Warning, TEXT("Swap & Join Failed"));
//	return false;
//}
//
//bool UInventoryComponent::UseItemInInventory(int32 InventoryIndex)
//{
//
//	if (InventoryArray.IsValidIndex(InventoryIndex)) // check valid
//	{
//		if (IsValid(InventoryArray[InventoryIndex].ItemData.ItemClass)) // check class exist
//		{
//			FActorSpawnParameters spawnParam;
//			spawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//			spawnParam.Owner = GetOwner();
//
//			AItem* item = GetWorld()->SpawnActor<AItem>(InventoryArray[InventoryIndex].ItemData.ItemClass, spawnParam);
//			if (item)
//			{
//				//Disable the Physical Existence
//				item->SetActorEnableCollision(false);
//				item->SetActorHiddenInGame(true);
//				item->SetActorTickEnabled(false);
//
//				//Use Item
//				bool bSucceed = item->UseItem();
//				//item->SetLifeSpan(0.1f);
//
//				//if Item Use success
//				if (bSucceed)
//				{
//					// if Item Type is consumption, decrease item number.
//					if (InventoryArray[InventoryIndex].ItemData.ItemType == EItemType::Consumption)
//					{
//						PopItemFromInventory(InventoryIndex);
//						return true;
//					}
//					else //equipment?
//					{
//						return true;
//					}
//				}
//			}
//		}
//	}
//
//	return false;
//}
//
//bool UInventoryComponent::SpendMoney(int32 OutMoney)
//{
//	if (Money < OutMoney)
//	{
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(256,5.0f,FColor::Silver,TEXT("Can't Spend Money, Demand is Over the In-Hand"));
//		}
//
//		return false;
//	}
//	else
//	{
//		Money = FMath::Clamp(Money - OutMoney, 0, TNumericLimits<int32>::Max());
//		return true;
//	}
//
//}
//
//void UInventoryComponent::GainMoney(int32 InMoney)
//{
//	Money = FMath::Clamp(Money + InMoney, 0, TNumericLimits<int32>::Max());
//}
//
//bool UInventoryComponent::CheckEnoughMoney(int32 ToCompare)
//{
//	if (Money >= ToCompare)
//	{
//		return true;
//	}
//
//	return false;
//}
