// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "ItemSlot.h"
#include "../Base/BasicPlayerController.h"

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 30; i++) // "i < 30" can be revised.
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	InitInventoryWidget();
}

void UInventoryWidget::InitInventoryWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventorySlotNumber = i;
		ItemSlotArray[i]->UpdateItemSlot();
	}
}

void UInventoryWidget::UpdateInventoryWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateItemSlot();
	}
	UE_LOG(LogTemp, Warning, TEXT("UPDATE Success"));
}
