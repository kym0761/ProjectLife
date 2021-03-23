// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageWidgetBase.h"
#include "Components/UniformGridPanel.h"
#include "../Inventory/ItemSlotBase.h"
#include "../Inventory/InventoryComponent.h"

void UStorageWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	//GridPanel = Cast<UUniformGridPanel>(GetWidgetFromName(TEXT("UniformGridPanel")));

	for (int32 i = 0; i < 20; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlotBase* slot = Cast<UItemSlotBase>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

}

void UStorageWidgetBase::InitStorage(AActor* StorageActorRef)
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

void UStorageWidgetBase::UpdateStorage()
{

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateSlot();
	}
	
}
