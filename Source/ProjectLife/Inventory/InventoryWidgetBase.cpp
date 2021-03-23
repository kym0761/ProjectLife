// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "ItemSlotBase.h"
#include "InventoryComponent.h"
#include "../Base/BasicPlayerController.h"
#include "EquipSlotBase.h"
#include "EquipmentComponent.h"


void UInventoryWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 30; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlotBase* slot = Cast<UItemSlotBase>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	InitInventoryWidget();
}

void UInventoryWidgetBase::InitInventoryWidget()
{
	if (IsValid(GetOwningPlayer()))
	{
		UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();
		
		if (IsValid(inventory))
		{
			for (int32 i = 0; i < ItemSlotArray.Num(); i++)
			{
				ItemSlotArray[i]->InventoryRef = inventory;
				ItemSlotArray[i]->InventoryIndex = i;
				ItemSlotArray[i]->UpdateSlot();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("failed?"));
		}
	}
}

void UInventoryWidgetBase::UpdateInventoryWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateSlot();
	}

}
