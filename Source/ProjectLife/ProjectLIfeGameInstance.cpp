// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLIfeGameInstance.h"
#include "Quest/QuestBase.h"

void UProjectLIfeGameInstance::AddQuest(UQuestBase* InQuest)
{
	if (!IsValid(InQuest))
	{
		return;
	}

	bool bCanAdd = true;
	for (int32 i = 0; i < Quests.Num(); i++)
	{
		if (Quests[i]->GetClass() == InQuest->GetClass())
		{
			bCanAdd = false;
		}
	}
	for (int32 i = 0; i < CompleteQuests.Num(); i++)
	{
		if (CompleteQuests[i]->GetClass() == InQuest->GetClass())
		{
			bCanAdd = false;
		}
	}


	if (bCanAdd)
	{
		Quests.Add(InQuest);
	}
}

void UProjectLIfeGameInstance::HandleQuestClear(UQuestBase* ClearedQuest)
{
	if (!IsValid(ClearedQuest))
	{
		return;
	}

	int32 questIndex = -1;
	for (int32 i = 0; i < Quests.Num(); i++)
	{
		if (Quests[i]->GetClass() == ClearedQuest->GetClass())
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
