// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectLIfeGameInstance.generated.h"

class UQuestBase;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UProjectLIfeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameInstance")
		TArray<UQuestBase*> Quests;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameInstance")
		TArray<UQuestBase*> CompleteQuests;

	UFUNCTION(BlueprintCallable)
		void AddQuest(UQuestBase* InQuest);

	void HandleQuestClear(UQuestBase* ClearedQuest);
};
