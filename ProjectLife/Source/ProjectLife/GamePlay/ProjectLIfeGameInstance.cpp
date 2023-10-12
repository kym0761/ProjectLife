// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLIfeGameInstance.h"
#include "Item/ItemStruct.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryComponent.h"
#include "Storage/StorageBox.h"
#include "GamePlay/ProjectLifeSaveGame.h"
#include "Base/BasicPlayerController.h"

FInventory::FInventory()
{
	//현재 인벤토리 당 슬롯 갯수는 30개.
	Money = 0;
	MaxCapacity = 30;

	for (int i = 0; i < 30; i++)
	{
		Items.Add(FItemSlotData());
	}
}

FItemData UProjectLIfeGameInstance::GetItemDataFromTable(FString Name)
{
	if (!(Name.Len() > 0))
	{
		return FItemData();
	}

	if (IsValid(ItemDataTable))
	{
		FItemData* itemData = ItemDataTable->FindRow<FItemData>(FName(*Name), "");

		if (itemData != nullptr)
		{
			return *itemData; // Some Issue Potentially?
		}
	}

	return FItemData();
}

FEquipmentItemData UProjectLIfeGameInstance::GetEquipmentItemDataFromTable(FString Name)
{

	if (!(Name.Len() > 0))
	{
		return FEquipmentItemData();
	}


	if (IsValid(EquipmentDataTable))
	{
		FEquipmentItemData* EquipmentData = EquipmentDataTable->FindRow<FEquipmentItemData>(FName(*Name), "");

		if (EquipmentData != nullptr)
		{
			return *EquipmentData; // Some Issue Potentially?
		}
	}

	return FEquipmentItemData();
}

void UProjectLIfeGameInstance::AddQuest(FString QuestName)
{
	//if (!IsValid(InQuest))
	//{
	//	return;
	//}

	//bool bCanAdd = true;
	//for (int32 i = 0; i < Quests.Num(); i++)
	//{
	//	if (Quests[i] == InQuest)
	//	{
	//		bCanAdd = false;
	//		if (GEngine)
	//		{

	//			FString txt = FString("Quest Already Existed");
	//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
	//		}
	//	}
	//}

	//for (int32 i = 0; i < CompleteQuests.Num(); i++)
	//{
	//	if (CompleteQuests[i] == InQuest)
	//	{
	//		bCanAdd = false;
	//		if (GEngine)
	//		{

	//			FString txt = FString("Quest Already Cleared");
	//			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
	//		}
	//	}
	//}

	//if (bCanAdd)
	//{
	//	Quests.Add(InQuest);

	//	if (GEngine)
	//	{
	//		FString questName = InQuest.GetDefaultObject()->QuestName;
	//		FString txt = questName + FString(" is Added");
	//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
	//	}
	//}


}

TArray<FQuest> UProjectLIfeGameInstance::GetAllQuests()
{
	return QuestList;
}

void UProjectLIfeGameInstance::ClearQuest(FString QuestName)
{
}

//void UProjectLIfeGameInstance::QuestClear(TSubclassOf<UQuest> WantToClear)
//{
//	if (!IsValid(WantToClear))
//	{
//		return;
//	}
//
//	int32 questIndex = -1;
//	for (int32 i = 0; i < Quests.Num(); i++)
//	{
//		if (Quests[i] == WantToClear)
//		{
//			questIndex = i;
//			break;
//		}
//	}
//
//	if (questIndex >= 0 && Quests.IsValidIndex(questIndex))
//	{
//		CompleteQuests.Add(Quests[questIndex]);
//		Quests.RemoveAt(questIndex);
//	}
//}

void UProjectLIfeGameInstance::GetAllInventories()
{
	TArray<AActor*> playerControllerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllerArray);

	for (int32 i = 0; i < playerControllerArray.Num(); i++)
	{
		UInventoryComponent* inventoryComponent = playerControllerArray[i]->FindComponentByClass<UInventoryComponent>();
		
		if (!IsValid(inventoryComponent))
		{
			continue;
		}

		//TODO? : 플레이어 ID에 따라 정확하게 저장하기?

		PlayerInventory.Add(i, FInventory());
		PlayerInventory[i].Items = inventoryComponent->GetItems();
		PlayerInventory[i].Money = inventoryComponent->GetMoney();
	}

	TArray<AActor*> storageArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageBox::StaticClass(), storageArray);

	for (int32 i = 0; i < storageArray.Num(); i++)
	{
		UInventoryComponent* inventoryComponent = storageArray[i]->FindComponentByClass<UInventoryComponent>();

		if (!IsValid(inventoryComponent))
		{
			continue;
		}

		//TODO? : StorageBox ID에 따라 정확하게 저장하기?

		StorageInventory.Add(i, FInventory());
		StorageInventory[i].Items = inventoryComponent->GetItems();
		StorageInventory[i].Money = inventoryComponent->GetMoney();
	}


}

void UProjectLIfeGameInstance::SetAllInventories()
{
	TArray<AActor*> playerControllerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerController::StaticClass(), playerControllerArray);

	for (int32 i = 0; i < playerControllerArray.Num(); i++)
	{
		UInventoryComponent* inventoryComponent = playerControllerArray[i]->FindComponentByClass<UInventoryComponent>();

		if (!IsValid(inventoryComponent))
		{
			continue;
		}

		inventoryComponent->SetItems(PlayerInventory[i].Items);
		inventoryComponent->SetMoney(PlayerInventory[i].Money);
	}


	TArray<AActor*> storageArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStorageBox::StaticClass(), storageArray);

	for (int32 i = 0; i < storageArray.Num(); i++)
	{
		UInventoryComponent* inventoryComponent = storageArray[i]->FindComponentByClass<UInventoryComponent>();

		if (!IsValid(inventoryComponent))
		{
			continue;
		}

		//TODO? : StorageBox ID에 따라 정확하게 저장하기?
		inventoryComponent->SetItems(StorageInventory[i].Items);
		inventoryComponent->SetMoney(StorageInventory[i].Money);
	}

	ABasicPlayerController* playerController = Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (playerController)
	{
		//playerController->UpdateInventory();
		playerController->UpdateEquipment();
	}
}

void UProjectLIfeGameInstance::Save()
{
	GetAllInventories();

	UProjectLifeSaveGame* saveGame =
		Cast<UProjectLifeSaveGame>(UGameplayStatics::CreateSaveGameObject(UProjectLifeSaveGame::StaticClass()));

	if (!IsValid(saveGame))
	{
		//save Failed
		return;
	}

	saveGame->PlayerInventory = PlayerInventory;
	saveGame->StorageInventory = StorageInventory;
	saveGame->SaveSlotName = FString("temp");
	saveGame->UserIndex = 1;

	UGameplayStatics::SaveGameToSlot(saveGame, saveGame->SaveSlotName, saveGame->UserIndex);

	UE_LOG(LogTemp, Warning, TEXT("Save OK"));
}

void UProjectLIfeGameInstance::Load()
{
	FString	saveSlotName = FString("temp");
	int32 userIndex = 1;

	UProjectLifeSaveGame* saveGame 
		= Cast<UProjectLifeSaveGame>(UGameplayStatics::LoadGameFromSlot(saveSlotName, userIndex));

	if (!IsValid(saveGame))
	{
		//Load Fail.
		return;
	}

	PlayerInventory = saveGame->PlayerInventory;
	StorageInventory = saveGame->StorageInventory;

	UE_LOG(LogTemp, Warning, TEXT("Load"));

	SetAllInventories();
}
