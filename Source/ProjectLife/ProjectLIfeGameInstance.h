// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Item/ItemStruct.h"
#include "GamePlay/GameTimeStruct.h"
#include "ProjectLIfeGameInstance.generated.h"

class UQuest;
class UDataTable;
/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UProjectLIfeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameInstance")
		TArray<TSubclassOf<UQuest>> Quests;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameInstance")
		TArray<TSubclassOf<UQuest>> CompleteQuests;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
		UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameInstance")
		UDataTable* EquipmentDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameInstance")
		FGameTime GameTime = FGameTime();

	UFUNCTION(BlueprintCallable)
		void AddQuest(TSubclassOf<UQuest> InQuest);

	UFUNCTION(BlueprintCallable)
	void QuestClear(TSubclassOf<UQuest> WantToClear);


	FItemData GetItemDataFromTable(FString Name);
	FEquipmentItemData GetEquipmentItemDataFromTable(FString Name);

};
