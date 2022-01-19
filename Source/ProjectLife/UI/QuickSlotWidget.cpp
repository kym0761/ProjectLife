// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "Components/HorizontalBox.h"
//#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/ItemSlot.h"


void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 10; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	InitQuickSlot();

}

void UQuickSlotWidget::InitQuickSlot()
{

	//if (IsValid(GetOwningPlayer()))
	//{
	//	UInventoryComponent* inventory = GetOwningPlayer()->GetPawn()->FindComponentByClass<UInventoryComponent>();

	//	if (IsValid(inventory))
	//	{
	//		for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	//		{
	//			ItemSlotArray[i]->InventoryRef = inventory;
	//			ItemSlotArray[i]->InventoryIndex = i;
	//			ItemSlotArray[i]->UpdateSlot();
	//		}
	//	}
	//	else
	//	{
	//		UE_LOG(LogTemp, Warning, TEXT("failed?"));
	//	}
	//}
}

void UQuickSlotWidget::UpdateQuickSlot()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventorySlotNumber = i;
		ItemSlotArray[i]->UpdateItemSlot();
	}
}
