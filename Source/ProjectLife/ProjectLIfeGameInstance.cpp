// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLIfeGameInstance.h"
#include "Quest/QuestBase.h"

void UProjectLIfeGameInstance::AddQuest(TSubclassOf<UQuestBase> InQuest)
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

void UProjectLIfeGameInstance::QuestClear(TSubclassOf<UQuestBase> WantToClear)
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
