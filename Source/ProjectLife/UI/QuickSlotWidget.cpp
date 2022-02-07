// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/ItemSlot.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryManager.h"

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 10; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		QuickSlotArray.Add(slot);
	}

	InitQuickSlot();

}

void UQuickSlotWidget::InitQuickSlot()
{
	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		for (int32 i = 0; i < QuickSlotArray.Num(); i++)
		{
			//플레이어의 인벤토리 넘버는 0이므로 0 대입.
			QuickSlotArray[i]->InventoryNumber = 0;
			QuickSlotArray[i]->InventorySlotNumber = i;
		}
		UpdateQuickSlot();
	}
}

void UQuickSlotWidget::UpdateQuickSlot()
{
	for (int32 i = 0; i < QuickSlotArray.Num(); i++)
	{
		QuickSlotArray[i]->UpdateItemSlot();
	}
}
