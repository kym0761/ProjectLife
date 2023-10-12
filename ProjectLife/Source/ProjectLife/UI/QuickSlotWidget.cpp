// Fill out your copyright notice in the Description page of Project Settings.


#include "QuickSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Base/BasicCharacter.h"
#include "Inventory/ItemSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryComponent.h"

void UQuickSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UQuickSlotWidget::InitQuickSlot()
{
	for (int32 i = 0; i < 10; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		QuickSlotArray.Add(slot);
	}

	for (int32 i = 0; i < QuickSlotArray.Num(); i++)
	{
		//플레이어 컨트롤러가 인벤토리를 보유할 예정.
		QuickSlotArray[i]->InitItemSlot(GetOwningPlayer());
		QuickSlotArray[i]->InventorySlotNumber = i;
	}

	UpdateQuickSlot();

	UInventoryComponent* inventoryComponent = GetOwningPlayer()->FindComponentByClass<UInventoryComponent>();

	if (IsValid(inventoryComponent))
	{
		inventoryComponent->
			OnInventoryDataChanged.AddDynamic(this, &UQuickSlotWidget::UpdateQuickSlot);
	}
}

void UQuickSlotWidget::UpdateQuickSlot()
{
	for (int32 i = 0; i < QuickSlotArray.Num(); i++)
	{
		QuickSlotArray[i]->UpdateItemSlot();
	}
}

bool UQuickSlotWidget::Initialize()
{
	bool succeed = Super::Initialize();

	if (!succeed)
	{
		return false;
	}

	InitQuickSlot();

	return true;
}
