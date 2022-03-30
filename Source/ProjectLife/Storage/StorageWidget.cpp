// Fill out your copyright notice in the Description page of Project Settings.


#include "StorageWidget.h"
#include "Components/UniformGridPanel.h"
#include "../Inventory/ItemSlot.h"
#include "StorageBox.h"
#include "../Inventory/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

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

void UStorageWidget::InitStorageWidget(AActor* StorageActorRef)
{

	//UE_LOG(LogTemp, Warning, TEXT("INIT Storage Widget"));

	//보관함과 inventoryManager에 접근하고 ItemSlot에 해당 정보를 대입함.
	AStorageBox* storageBox = Cast<AStorageBox>(StorageActorRef);

	if (!IsValid(storageBox))
	{
		return;
	}

	UInventoryComponent* inventoryComponent = storageBox->FindComponentByClass<UInventoryComponent>();

	if (!IsValid(inventoryComponent))
	{
		return;
	}

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventoryComponentRef = inventoryComponent;
		ItemSlotArray[i]->InventorySlotNumber = i;
	}

	UpdateStorageWidget();

}

void UStorageWidget::UpdateStorageWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateItemSlot();
	}	
}
