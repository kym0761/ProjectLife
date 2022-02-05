// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Inventory/InventoryManager.h"
#include "ProjectLifeSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UProjectLifeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;

    UPROPERTY(VisibleAnywhere, Category = Basic)
        TMap<int32, FInventory> Inventories;

    UProjectLifeSaveGame();

};
