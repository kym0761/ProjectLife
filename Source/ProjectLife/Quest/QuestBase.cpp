// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestBase.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/StatComponent.h"
#include "../Item/Item.h"
#include "../ProjectLIfeGameInstance.h"
UQuestBase::UQuestBase()
{
	bHideObjective = false;
	QuestSequenceNumber = 0;
}

UGameInstance* UQuestBase::GetCurrentGameInstance() const
{
	if (GetWorld())
	{
	return UGameplayStatics::GetGameInstance(GetWorld());
	}
	
	return nullptr;
}

void UQuestBase::ObjectiveClear()
{
	if (bHideObjective)
	{
		bool validNum = QuestObjectives.IsValidIndex(QuestSequenceNumber);
		if (validNum)
		{
			QuestSequenceNumber++;
		}
	}

}

void UQuestBase::QuestClear(APawn* QuestReceiver)
{
	UInventoryComponent* inventory = QuestReceiver->FindComponentByClass<UInventoryComponent>();
	UStatComponent* stat = QuestReceiver->FindComponentByClass<UStatComponent>();

	for (FReward ob : QuestRewards)
	{
		switch (ob.QuestRewardType)
		{
		case EQuestReward::Money:
			if (IsValid(inventory))
			{
				inventory->GainMoney(ob.RewardMoney);
			}
			break;
		case EQuestReward::Experience:
			if (IsValid(stat))
			{
				stat->Experience += ob.RewardExperience;
			}
			break;
		case EQuestReward::Item:
			if (IsValid(inventory))
			{
				FItemDataStruct itemData= ob.RewardItem->GetDefaultObject<AItem>()->ItemData;
				inventory->AddItemToInventory(itemData);
			}
			break;
		case EQuestReward::None:
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.5f,FColor::Orange,TEXT("Reward Not Confirmed"));
			}
			break;
		default :
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Orange, TEXT("the Unknown Reward"));
			}
			break;
		}
	}

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Orange, TEXT("Quest Clear Called."));
	//}

	if (GetWorld())
	{
		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (gameInstance)
		{
			gameInstance->HandleQuestClear(this);
		}
	}

}
