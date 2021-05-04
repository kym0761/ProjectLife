// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSlotBase.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "ItemSlotBase.h"
#include "InventoryComponent.h"
#include "EquipmentComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Base/BasicPlayerController.h"


void UEquipSlotBase::NativeConstruct()
{
	Super::NativeConstruct();

	SetVisibility(ESlateVisibility::Visible);
}

FReply UEquipSlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (GEngine)
	{
		UEnum* enumptr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEquipmentType"), true);
		if (enumptr)
		{
			FString enumString = enumptr->GetNameStringByIndex((uint8)SlotEquipmentType);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, enumString);
		}
	}

	//Drag Function Activate.
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);

	return reply.NativeReply;

}

void UEquipSlotBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	
	if (IsValid(EquipmentCompRef))
	{
		UEquipmentItemData* equipmentItemData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);

		if (IsValid(equipmentItemData))
		{
			if (IsValid(EquipSlotClass))
			{
				UEquipSlotBase* dragDisplay = CreateWidget<UEquipSlotBase>(GetOwningPlayer(), EquipSlotClass);

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

bool UEquipSlotBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//UE_LOG(LogTemp, Warning, TEXT("Equip Slot Base Native On Drop"));

	if (InOperation)
	{
		//if drop is Item Slot
		{
			UItemSlotBase* dropped = Cast<UItemSlotBase>(InOperation->Payload);
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
					//else
					//{
					//	if (GEngine)
					//	{
					//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("It is not a Equipment."));
					//	}
					//}
				}
			}
		}

		//if drop is Equip slot. Maybe Accessory? ex) accessory1 <->accessory2 swap.
		{
			UEquipSlotBase* dropped = Cast<UEquipSlotBase>(InOperation->Payload);
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
	//else
	//{
	//	if (GEngine)
	//	{
	//		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("InOperation is Not Valid."));
	//	}
	//}

	return false;
}

void UEquipSlotBase::UpdateSlot()
{
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
