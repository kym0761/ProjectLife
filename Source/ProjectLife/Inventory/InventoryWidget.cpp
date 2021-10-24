// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"
#include "Components/UniformGridPanel.h"
#include "ItemSlot.h"
#include "InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
#include "../Equipment/EquipSlot.h"
#include "../Equipment/EquipmentComponent.h"


void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 30; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	InitInventoryWidget();
}

void UInventoryWidget::InitInventoryWidget()
{
	if (IsValid(GetOwningPlayer()))
	{
		UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
		
		//Add ItemSlot in Inventory UI.
		if (IsValid(inventory))
		{
			for (int32 i = 0; i < ItemSlotArray.Num(); i++)
			{
				ItemSlotArray[i]->InventoryRef = inventory;
				ItemSlotArray[i]->InventoryIndex = i;
				ItemSlotArray[i]->UpdateSlot();
			}
		}
		//else
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("failed?"));
		//}
	}
}

void UInventoryWidget::UpdateInventoryWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateSlot();
	}

}
