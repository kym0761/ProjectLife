// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageWidget.h"
#include "Components/UniformGridPanel.h"
#include "../Inventory/ItemSlot.h"
#include "../Inventory/InventoryComponent.h"

void UStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//GridPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel")));

	for (int32 i = 0; i < 20; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

}

void UStorageWidget::InitStorage(AActor* StorageActorRef)
{
	UInventoryComponent* inventoryComp = StorageActorRef->FindComponentByClass<UInventoryComponent>();

	if (inventoryComp)
	{
		if (inventoryComp->InventoryArray.IsValidIndex(ItemSlotArray.Num() - 1))
		{
			for (int32 i = 0; i < ItemSlotArray.Num(); i++)
			{
				ItemSlotArray[i]->InventoryRef = inventoryComp;
				ItemSlotArray[i]->InventoryIndex = i;
				ItemSlotArray[i]->UpdateSlot();
			}
		}
	}
}

void UStorageWidget::UpdateStorage()
{

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateSlot();
	}
	
}
