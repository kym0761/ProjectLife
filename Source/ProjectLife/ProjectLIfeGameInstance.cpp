// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLIfeGameInstance.h"
#include "Item/ItemStruct.h"

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
