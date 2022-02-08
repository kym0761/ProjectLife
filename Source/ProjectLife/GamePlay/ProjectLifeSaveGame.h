// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "../Inventory/InventoryManager.h"
#include "ProjectLifeSaveGame.generated.h"

/**
 * Ver 1.0
 */
UCLASS()
class PROJECTLIFE_API UProjectLifeSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

    UProjectLifeSaveGame();

    //?
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString PlayerName;

    //Default SaveSlotName
    UPROPERTY(VisibleAnywhere, Category = Basic)
        FString SaveSlotName;


    //Default UserIndex
    UPROPERTY(VisibleAnywhere, Category = Basic)
        uint32 UserIndex;

    ////Inventory Save
    //UPROPERTY(VisibleAnywhere, Category = Basic)
    //    TMap<int32, FInventory> Inventories;

};
