// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DataTable.h"
#include "Quest.generated.h"

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	None UMETA(DisplayName = "None"),
	MainQuest UMETA(DisplayName = "MainQuest"),
	SideQuest UMETA(DisplayName = "SideQuest"),
	PartTimeJob UMETA(DisplayName = "PartTimeJob")
};

UENUM(BlueprintType)
enum class EObjectiveType : uint8
{
	None UMETA(DisplayName = "None"),
	Collect UMETA(DisplayName = "Collect"),
	Slay UMETA(DisplayName = "Slay"),
	GoSomewhere UMETA(DisplayName = "GoSomewhere")
};

UENUM(BlueprintType)
enum class EQuestRewardType : uint8
{
	None UMETA(DisplayName = "None"),
	Money UMETA(DisplayName = "Money"),
	Experience UMETA(DisplayName = "Experience"),
	Item UMETA(DisplayName = "Item"),
};

USTRUCT(BlueprintType)
struct FReward 
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		EQuestRewardType QuestRewardType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		int32 RewardMoney;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		int32 RewardExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		FString RewardItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reward")
		int32 RewardItemAmount;
};

USTRUCT(BlueprintType)
struct FObjective
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		EObjectiveType ObjectiveType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		TSubclassOf<AActor> EnemyToSlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		FString ItemNameToCollect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
		int32 Number;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Objective")
	//	AActor* WhereToGo;

};

USTRUCT(BlueprintType)
struct FQuest : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FString QuestName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FString QuestDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		EQuestType QuestType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FObjective> QuestObjectives;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FReward> QuestRewards;

};


///**
// * 
// */
//UCLASS(BlueprintType, Blueprintable)
//class PROJECTLIFE_API UQuest : public UObject
//{
//	GENERATED_BODY()
//
//public:
//
//	UQuest();
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
//		FString QuestName;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
//		FString QuestDescription;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
//		TArray<FObjective> QuestObjectives;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
//		TArray<FReward> QuestRewards;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
//		bool bHideObjective;
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
//		int32 QuestSequenceNumber;
//
//	UFUNCTION(BlueprintCallable)
//		class UGameInstance* GetCurrentGameInstance() const;
//
//	void ObjectiveClear(); // Not Ready.
//
//	UFUNCTION(BlueprintCallable)
//	void QuestClear(APawn* QuestReceiver);
//};
