// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSlot.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "ItemSlot.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Base/BasicPlayerController.h"


void UEquipSlot::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

FReply UEquipSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	//if (GEngine)
	//{
	//	UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEquipmentType"), true);
	//	if (enumptr)
	//	{
	//		FString enumString = enumptr->GetNameStringByIndex((uint8)SlotEquipmentType);
	//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, enumString);
	//	}
	//}

	//Drag Function Activate.
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return reply.NativeReply;

}

void UEquipSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	//Make New Equip Slot For Drag.
	if (IsValid(EquipmentCompRef))
	{
		UEquipmentItemData* equipmentItemData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);

		if (IsValid(equipmentItemData))
		{
			if (IsValid(EquipSlotClass))
			{
				UEquipSlot* dragDisplay = CreateWidget<UEquipSlot>(GetOwningPlayer(), EquipSlotClass);

				if (IsValid(dragDisplay))
				{
					if (IsValid(equipmentItemData->Thumbnail))
					{
						dragDisplay->SlotImage->SetBrushFromTexture(equipmentItemData->Thumbnail);
					}

					UDragDropOperation* dragDropOper = NewObject<UDragDropOperation>();
					dragDropOper->Payload = this;
					dragDropOper->DefaultDragVisual = dragDisplay;
					dragDropOper->Pivot = EDragPivot::CenterCenter;

					OutOperation = dragDropOper;
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("EquipSlotClass is not Exist. Set Equip Class First."));
			}
		}
	}
}

bool UEquipSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);



	if (InOperation)
	{
		//if a dropped slot is a Item Slot
		//Get ItemData And Equip it if it is EquipmentData.
		{
			UItemSlot* dropped = Cast<UItemSlot>(InOperation->Payload);
			if (IsValid(dropped))
			{
				//Get Drop's Inventory & Index
				UInventoryComponent* inventoryRef = dropped->InventoryRef;
				int32 index = dropped->InventoryIndex;

				if (IsValid(inventoryRef) && IsValid(EquipmentCompRef))
				{
					//Inventory Data of Valid Index.
					FItemDataSlot itemDataSlot = inventoryRef->InventoryArray[index];
					if (IsValid(itemDataSlot.ItemData))
					{

						UItemData* itemData = itemDataSlot.ItemData.GetDefaultObject();
						if (IsValid(itemData))
						{
							UEquipmentItemData* equipmentItemData = Cast<UEquipmentItemData>(itemData);
							if (IsValid(equipmentItemData))
							{
								if (equipmentItemData->EquipmentType == SlotEquipmentType)
								{
									UEquipmentItemData* currentEquipment = EquipmentCompRef->GetEquipmentData(EquipmentSlot);

									bool bSucceed = EquipmentCompRef->SetEquipment(EquipmentSlot, equipmentItemData);
									if (bSucceed)
									{
										//Equipment item Data is Valid, set slot's Values.
										//if not, Reset slot's Values.
										if (IsValid(currentEquipment))
										{
											FItemDataSlot temp;
											temp.ItemData = currentEquipment->GetClass();
											temp.Quantity = 1;
											inventoryRef->InventoryArray[index] = temp;
										}
										else
										{
											FItemDataSlot temp;
											temp.Quantity = 0;
											inventoryRef->InventoryArray[index] = temp;
										}

										ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
										if (playerController)
										{
											playerController->UpdateInventory();
										}
										return true;
									}
								}
							}
						}
					}
				}
			}
		}

		//if drop is Equip slot. Maybe Accessory? ex) accessory1 <->accessory2 swap.
		//other Equipment Slot Will not Valid.. because there is no other Weapon Slot or Armor slot, etc... in game...
		{
			UEquipSlot* dropped = Cast<UEquipSlot>(InOperation->Payload);
			if (IsValid(dropped))
			{
				if (IsValid(dropped->EquipmentCompRef) && IsValid(EquipmentCompRef) && EquipmentSlot == dropped->EquipmentSlot)
				{
					UEquipmentItemData* CurrentEquipmentData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);
					UEquipmentItemData* droppedEquipmentData = dropped->EquipmentCompRef->GetEquipmentData(dropped->EquipmentSlot);
					
					if (IsValid(CurrentEquipmentData) && IsValid(droppedEquipmentData))
					{
						dropped->EquipmentCompRef->SetEquipment(dropped->EquipmentSlot, CurrentEquipmentData);
						EquipmentCompRef->SetEquipment(EquipmentSlot, droppedEquipmentData);

						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							playerController->UpdateInventory();
						}

						return true;

					}
				}
			}
		}
	}

	return false;
}

void UEquipSlot::UpdateSlot()
{
	//Update Slot with Current Data.

	if (EquipmentCompRef)
	{
		UEquipmentItemData* equipmentItemData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);
		if (IsValid(equipmentItemData))
		{
			if (IsValid(SlotImage) && IsValid(equipmentItemData->Thumbnail))//Set Image
			{
				SlotImage->SetBrushFromTexture(equipmentItemData->Thumbnail);
				//UE_LOG(LogTemp, Warning, TEXT("Image Updated"));
			}
		}

	}
}
