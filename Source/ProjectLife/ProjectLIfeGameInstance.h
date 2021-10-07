// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectLIfeGameInstance.generated.h"

class UQuest;

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

	UFUNCTION(BlueprintCallable)
		void AddQuest(TSubclassOf<UQuest> InQuest);

	UFUNCTION(BlueprintCallable)
	void QuestClear(TSubclassOf<UQuest> WantToClear);
};
