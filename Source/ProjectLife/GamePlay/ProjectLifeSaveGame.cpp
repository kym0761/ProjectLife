// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectLifeSaveGame.h"

UProjectLifeSaveGame::UProjectLifeSaveGame()
{
	SaveSlotName = FString("GameSaveSlot");
	UserIndex = 0;

	//인벤토리 숫자 현재 10, 늘리고 싶으면 수정 필요함.
	for (int32 i = 0; i < 100; i++)
	{
		FInventory inventory;
		Inventories.Add(i, inventory);
	}
}