// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidgetBase.h"
#include "Components/HorizontalBox.h"
#include "../Inventory/InventoryComponent.h"
#include "../Base/BasicCharacter.h"
#include "../Inventory/ItemSlotBase.h"


void UQuickSlotWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 10; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlotBase* slot = Cast<UItemSlotBase>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	InitQuickSlot();

}

void UQuickSlotWidgetBase::InitQuickSlot()
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

void UQuickSlotWidgetBase::UpdateQuickSlot()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateSlot();
	}
}
