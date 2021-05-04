// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotBase.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Item/Item.h"
#include "../Base/BasicCharacter.h"
#include "InventoryComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Base/BasicPlayerController.h"
#include "EquipSlotBase.h"
#include "EquipmentComponent.h"

//#include "Kismet/KismetInputLibrary.h"
//#include "Blueprint/SlateBlueprintLibrary.h"

void UItemSlotBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::Visible);
}

FReply UItemSlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry,InMouseEvent);

	//Drag Function Activate.
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	return reply.NativeReply;
}

void UItemSlotBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry,InMouseEvent,OutOperation);

	if (IsValid(InventoryRef))
	{
		if (IsValid(InventoryRef->InventoryArray[InventoryIndex].ItemData))
		{
			UItemData* itemData = InventoryRef->InventoryArray[InventoryIndex].ItemData.GetDefaultObject();

			if (IsValid(itemData))
			{
				if (IsValid(ItemSlotClass))
				{
					//Create DragDisplayUI
					UItemSlotBase* dragDisplay = CreateWidget<UItemSlotBase>(GetOwningPlayer(), ItemSlotClass);

					if (IsValid(dragDisplay))
					{
						//Set Default Image and Number.
						if (itemData->Thumbnail)
						{
							dragDisplay->SlotImage->SetBrushFromTexture(itemData->Thumbnail);
						}
						dragDisplay->SlotItemNum->SetText(FText::GetEmpty());

						//Make DragDropEvent And Assign it.
						UDragDropOperation* dragDropOper = NewObject<UDragDropOperation>();
						dragDropOper->Payload = this;
						dragDropOper->DefaultDragVisual = dragDisplay;
						dragDropOper->Pivot = EDragPivot::CenterCenter;

						OutOperation = dragDropOper;
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("dragDisplay Create Failed."));
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ItemSlotClass is not Exist. Add Slot Class Please."));
	}
}

bool UItemSlotBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//check InOperation is Existed.
	if (InOperation)
	{
		/*ItemSlot*/
		{
			//Get Payload and Cast To ItemSlot.
			UItemSlotBase* droppedItemSlot = Cast<UItemSlotBase>(InOperation->Payload);

			if (IsValid(droppedItemSlot)) //Get InventoryRef & Index.
			{
				UInventoryComponent* droppedItemslot_Inventory = droppedItemSlot->InventoryRef;
				int32 droppedInventoryIndex = droppedItemSlot->InventoryIndex;

				if (IsValid(droppedItemslot_Inventory)) //Swap With it.
				{
					bool bSucceed = InventoryRef->SwapInventoryItem(InventoryIndex, droppedItemslot_Inventory, droppedInventoryIndex);

					if (bSucceed) // Update All Slot After Swap.
					{
						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							UE_LOG(LogTemp,Warning,TEXT("Attempt Update"));
							playerController->UpdateInventory();
						}
						return true;
					}
				}
			}
		}

		/*EquipSlot, similar With [Item Slot] code*/
		{
			UEquipSlotBase* droppedEquipSlot = Cast<UEquipSlotBase>(InOperation->Payload);
			if (IsValid( droppedEquipSlot))
			{
				UEquipmentComponent* equipmentComp = droppedEquipSlot->EquipmentCompRef;
				EEquipmentSlot droppedEquipmentslot = droppedEquipSlot->EquipmentSlot;

				if (equipmentComp)
				{
					bool bSucceed = equipmentComp->SwapWithInventory(droppedEquipmentslot, InventoryRef, InventoryIndex);
					if (bSucceed)
					{
						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							UE_LOG(LogTemp, Warning, TEXT("Attempt Update"));
							playerController->UpdateInventory();
						}
						return true;
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InOperation is Not Valid."));
	}


	return false;
}

FReply UItemSlotBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (InventoryRef)
	{
		bool bSucceed = InventoryRef->UseItemInInventory(InventoryIndex);
		if (bSucceed)
		{
			UpdateSlot();
		}
	}
	return FReply::Handled();
}

void UItemSlotBase::UpdateSlot()
{

	if (IsValid(InventoryRef) && InventoryRef->InventoryArray.IsValidIndex(InventoryIndex))
	{
		if (IsValid(InventoryRef->InventoryArray[InventoryIndex].ItemData))
		{
			UItemData* itemData = InventoryRef->InventoryArray[InventoryIndex].ItemData.GetDefaultObject();

			if (IsValid(itemData))
			{
				if (IsValid(SlotImage))//Set Image
				{
					if (IsValid(itemData->Thumbnail))
					{
						SlotImage->SetBrushFromTexture(itemData->Thumbnail);
					}
					else
					{
						SlotImage->SetBrushFromTexture(nullptr);
					}
				}

				if (IsValid(SlotItemNum))//Set Number
				{
					FText QuantityText;

					if (itemData->bIsStackable)
					{
						QuantityText = FText::FromString(FString::FromInt(InventoryRef->InventoryArray[InventoryIndex].Quantity));
					}
					else
					{
						QuantityText = FText::GetEmpty();
					}

					SlotItemNum->SetText(QuantityText);
				}
			}
		}
		else // set void
		{
			if (IsValid(SlotImage))
			{
				SlotImage->SetBrushFromTexture(nullptr);
			}
			if (IsValid(SlotItemNum))
			{
				SlotItemNum->SetText(FText::GetEmpty());
			}
		}	
	}
	else // set void
	{
		if (IsValid(SlotImage))
		{
			SlotImage->SetBrushFromTexture(nullptr);
		}
		if (IsValid(SlotItemNum))
		{
			SlotItemNum->SetText(FText::GetEmpty());
		}
	}
}


