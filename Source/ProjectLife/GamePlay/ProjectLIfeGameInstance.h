// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Item/ItemStruct.h"
#include "GamePlay/GameTimeStruct.h"
#include "Quest/Quest.h"
#include "ProjectLIfeGameInstance.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct FInventory
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FItemSlotData> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxCapacity;

	FInventory();

};

/**
 * 게임에서 공용으로 사용할 Data Table 들을 GameInstance 사용.
 */
UCLASS()
class PROJECTLIFE_API UProjectLIfeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

#pragma region dataTable

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
		UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
		UDataTable* EquipmentDataTable;

	FItemData GetItemDataFromTable(FString Name);
	FEquipmentItemData GetEquipmentItemDataFromTable(FString Name);

#pragma endregion

#pragma region quest
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Quest")
		TArray<FQuest> QuestList;

	UFUNCTION(BlueprintCallable)
		void AddQuest(FString QuestName);

	UFUNCTION(BlueprintCallable)
		TArray<FQuest> GetAllQuests();

	UFUNCTION(BlueprintCallable)
		void ClearQuest(FString QuestName);
#pragma endregion

#pragma region inventory
	/*Inventory Store Functions*/

	//0번째 유저만 쓸 예정, 후에 확장시 1 2 3... 에 배정
	TMap<int32, FInventory> PlayerInventory;

	//맵에 존재하는 상자들 저장
	TMap<int32, FInventory> StorageInventory;

	void GetAllInventories();
	void SetAllInventories();

	UFUNCTION(BlueprintCallable)
	void Save();
	UFUNCTION(BlueprintCallable)
	void Load();
#pragma endregion

};
