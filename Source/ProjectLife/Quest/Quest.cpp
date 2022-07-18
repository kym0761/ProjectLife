// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest.h"
#include "Kismet/GameplayStatics.h"
#include "Base/StatComponent.h"
#include "Item/Item.h"
#include "GamePlay/ProjectLIfeGameInstance.h"

//UQuest::UQuestBase()
//{
//	bHideObjective = false;
//	QuestSequenceNumber = 0;
//}
//
//UGameInstance* UQuest::GetCurrentGameInstance() const
//{
//	if (GetWorld())
//	{
//	return UGameplayStatics::GetGameInstance(GetWorld());
//	}
//	
//	return nullptr;
//}
//
//void UQuest::ObjectiveClear()
//{
//	if (bHideObjective)
//	{
//		bool validNum = QuestObjectives.IsValidIndex(QuestSequenceNumber);
//		if (validNum)
//		{
//			QuestSequenceNumber++;
//		}
//	}
//
//}
//
//void UQuest::QuestClear(APawn* QuestReceiver)
//{
//	/*
//	UInventoryComponent* inventory = QuestReceiver->FindComponentByClass<UInventoryComponent>();
//	UStatComponent* stat = QuestReceiver->FindComponentByClass<UStatComponent>();
//
//	for (FReward ob : QuestRewards)
//	{
//		switch (ob.QuestRewardType)
//		{
//		case EQuestReward::Money:
//			if (IsValid(inventory))
//			{
//				inventory->GainMoney(ob.RewardMoney);
//			}
//			break;
//		case EQuestReward::Experience:
//			if (IsValid(stat))
//			{
//				stat->Experience += ob.RewardExperience;
//			}
//			break;
//		case EQuestReward::Item:
//			if (IsValid(inventory))
//			{
//				FItemDataSlot itemData = ob.RewardItem->GetDefaultObject<AItem>()->ItemData;
//				inventory->AddItemToInventory(itemData);
//			}
//			break;
//		case EQuestReward::None:
//			if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(FMath::Rand(),2.5f,FColor::Orange,TEXT("Reward Not Confirmed"));
//			}
//			break;
//		default :
//			if (GEngine)
//			{
//				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Orange, TEXT("the Unknown Reward"));
//			}
//			break;
//		}
//	}
//
//	//if (GEngine)
//	//{
//	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.5f, FColor::Orange, TEXT("Quest Clear Called."));
//	//}
//
//	if (GetWorld())
//	{
//		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
//		if (gameInstance)
//		{
//			gameInstance->HandleQuestClear(this);
//		}
//	}
//	*/
//}
