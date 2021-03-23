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

	//SlotImage = Cast<UImage>(GetWidgetFromName(TEXT("SlotImage")));

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

	
	if (EquipmentCompRef)
	{
		//Null Equipment Slot Must Not Dragged
		if (EquipmentCompRef->GetEquipWithIndex(EquipmentIndex).Quantity == 0)
		{
			return;
		}
	}

	if (EquipSlotClass)
	{
		UEquipSlotBase* dragDisplay = CreateWidget<UEquipSlotBase>(GetOwningPlayer(), EquipSlotClass);

		if (dragDisplay)
		{
			dragDisplay->SlotImage->SetBrushFromTexture(EquipmentCompRef->GetEquipWithIndex(EquipmentIndex).Thumbnail);

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

bool UEquipSlotBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//UE_LOG(LogTemp, Warning, TEXT("Equip Slot Base Native On Drop"));

	if (InOperation)
	{
		//if drop is Item Slot
		{
			UItemSlotBase* dropped = Cast<UItemSlotBase>(InOperation->Payload);
			if (dropped)
			{
				//Get Drop's Inventory & Index
				UInventoryComponent* inventoryRef = dropped->InventoryRef;
				int32 index = dropped->InventoryIndex;

				if (inventoryRef)
				{
					//Inventory Data of Valid Index.
					FItemDataStruct itemData = inventoryRef->InventoryArray[index];

					//Do if ItemType is Equipment Type
					if (itemData.ItemType == EItemType::Equipment)
					{
						//assign to EquipmentComponent
						if (EquipmentCompRef)
						{

							//Do if ItemData's EquipmentType is Equal to SlotEquipmentType.
							if (itemData.EquipmentType == SlotEquipmentType)
							{
								//get Current Equipment.
								FItemDataStruct temp;
								temp = EquipmentCompRef->GetEquipWithIndex(EquipmentIndex);
								//Change Equipment.
								bool bSucceed = EquipmentCompRef->SetEquipWithIndex(EquipmentIndex, itemData);
								if (bSucceed)
								{
									inventoryRef->InventoryArray[index] = temp;


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
					else
					{
						if (GEngine)
						{
							GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("It is not a Equipment."));
						}
					}
				}
			}
		}

		//if drop is Equip slot. Maybe Accessory?
		{
			UEquipSlotBase* dropped = Cast<UEquipSlotBase>(InOperation->Payload);
			if (dropped)
			{
				FItemDataStruct droppedItemData = dropped->EquipmentCompRef->GetEquipWithIndex(dropped->EquipmentIndex);
				if (SlotEquipmentType == droppedItemData.EquipmentType)
				{
					//swap with current and dropped
					dropped->EquipmentCompRef->SetEquipWithIndex(dropped->EquipmentIndex, EquipmentCompRef->GetEquipWithIndex(EquipmentIndex));
					EquipmentCompRef->SetEquipWithIndex(EquipmentIndex, droppedItemData);


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
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("InOperation is Not Valid."));
		}
	}
	return false;
}

void UEquipSlotBase::UpdateSlot()
{
	if (EquipmentCompRef)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Access"));
		if (SlotImage)//Set Image
		{
			SlotImage->SetBrushFromTexture(EquipmentCompRef->GetEquipWithIndex(EquipmentIndex).Thumbnail);
			//UE_LOG(LogTemp, Warning, TEXT("Image Updated"));
		}
	}
}
