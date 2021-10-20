// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLIfeGameInstance.h"
#include "Quest/Quest.h"
#include "Item/ItemStruct.h"

void UProjectLIfeGameInstance::AddQuest(TSubclassOf<UQuest> InQuest)
{
	if (!IsValid(InQuest))
	{
		return;
	}

	bool bCanAdd = true;
	for (int32 i = 0; i < Quests.Num(); i++)
	{
		if (Quests[i] == InQuest)
		{
			bCanAdd = false;
			if (GEngine)
			{

				FString txt = FString("Quest Already Existed");
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
			}
		}
	}

	for (int32 i = 0; i < CompleteQuests.Num(); i++)
	{
		if (CompleteQuests[i] == InQuest)
		{
			bCanAdd = false;
			if (GEngine)
			{

				FString txt = FString("Quest Already Cleared");
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
			}
		}
	}

	if (bCanAdd)
	{
		Quests.Add(InQuest);

		if (GEngine)
		{
			FString questName = InQuest.GetDefaultObject()->QuestName;
			FString txt = questName + FString(" is Added");
			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Black, txt);
		}
	}


}

void UProjectLIfeGameInstance::QuestClear(TSubclassOf<UQuest> WantToClear)
{
	if (!IsValid(WantToClear))
	{
		return;
	}

	int32 questIndex = -1;
	for (int32 i = 0; i < Quests.Num(); i++)
	{
		if (Quests[i] == WantToClear)
		{
			questIndex = i;
			break;
		}
	}

	if (questIndex >= 0 && Quests.IsValidIndex(questIndex))
	{
		CompleteQuests.Add(Quests[questIndex]);
		Quests.RemoveAt(questIndex);
	}
}

FItemData UProjectLIfeGameInstance::GetItemDataFromTable(FString Name)
{
	if (IsValid(ItemDataTable))
	{
		FItemData* itemData = ItemDataTable->FindRow<FItemData>(FName(*Name), "");

		return *itemData; // Some Issue Potentially?
	}

	return FItemData();
}

FEquipmentItemData UProjectLIfeGameInstance::GetEquipmentItemDataFromTable(FString Name)
{
	if (IsValid(EquipmentDataTable))
	{
		FEquipmentItemData* EquipmentData = EquipmentDataTable->FindRow<FEquipmentItemData>(FName(*Name), "");

		return *EquipmentData; // Some Issue Potentially?
	}

	return FEquipmentItemData();
}
