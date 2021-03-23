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

	//SlotImage = Cast<UImage>(GetWidgetFromName(TEXT("SlotImage")));

	//SlotItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("SlotItemNum")));
	
	SetVisibility(ESlateVisibility::Visible);

	//UE_LOG(LogTemp, Warning, TEXT("%s"),*GetOwningPlayer()->GetName());
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

	if (InventoryRef)
	{
		//Null Item Slot Must Not Dragged.
		if (InventoryRef->InventoryArray[InventoryIndex].Quantity == 0)
		{
			return;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("NativeOnDragDetected"));
	if (ItemSlotClass)
	{
		//Create DragDisplayUI
		UItemSlotBase* dragDisplay = CreateWidget<UItemSlotBase>(GetOwningPlayer(), ItemSlotClass);
		
		if (dragDisplay)
		{
			//Set Default Image and Number.
			dragDisplay->SlotImage->SetBrushFromTexture(InventoryRef->InventoryArray[InventoryIndex].Thumbnail);
			dragDisplay->SlotItemNum->SetText(FText::GetEmpty());

			//FVector2D temp = UKismetInputLibrary::PointerEvent_GetScreenSpacePosition(InMouseEvent);
			//FVector2D temp2 = USlateBlueprintLibrary::AbsoluteToLocal(InGeometry,temp);

			//dragDisplay->SetPositionInViewport(temp2);

			//Make DragDropEvent And Assign it.
			UDragDropOperation* dragDropOper = NewObject<UDragDropOperation>();
			dragDropOper->Payload = this;
			dragDropOper->DefaultDragVisual = dragDisplay;
			dragDropOper->Pivot = EDragPivot::CenterCenter;
			
			

			OutOperation = dragDropOper;
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Player is Not Exist."));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("ItemSlotClass is not Exist. Add Slot Class Please."));
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

			if (droppedItemSlot) //Get InventoryRef & Index.
			{
				UInventoryComponent* droppedItemslot_Inventory = droppedItemSlot->InventoryRef;
				int32 droppedInventoryIndex = droppedItemSlot->InventoryIndex;

				if (droppedItemslot_Inventory) //Swap With it.
				{
					bool bSucceed = InventoryRef->SwapInventoryItem(InventoryIndex, droppedItemslot_Inventory, droppedInventoryIndex);

					if (bSucceed) // Update All Slot After Swap.
					{
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

		/*EquipSlot Same With [Item Slot] code*/
		{
			UEquipSlotBase* droppedEquipSlot = Cast<UEquipSlotBase>(InOperation->Payload);
			if (droppedEquipSlot)
			{

				UEquipmentComponent* equipmentComp = droppedEquipSlot->EquipmentCompRef;
				int32 droppedEquipmentIndex = droppedEquipSlot->EquipmentIndex;

				if (equipmentComp)
				{
					bool bSucceed = equipmentComp->SwapWithInventory(droppedEquipmentIndex, InventoryRef, InventoryIndex);
					if (bSucceed)
					{
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
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("InOperation is Not Valid."));
		}
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

	if (InventoryRef && InventoryRef->InventoryArray.IsValidIndex(InventoryIndex))
	{

		//UE_LOG(LogTemp, Warning, TEXT("Access"));
		if (SlotImage)//Set Image
		{
			SlotImage->SetBrushFromTexture(InventoryRef->InventoryArray[InventoryIndex].Thumbnail);
			//UE_LOG(LogTemp, Warning, TEXT("Image Updated"));
		}

		if (SlotItemNum)//Set Number
		{
			FText QuantityText;

			if (InventoryRef->InventoryArray[InventoryIndex].bIsStackable)
			{
				QuantityText = FText::FromString(FString::FromInt(InventoryRef->InventoryArray[InventoryIndex].Quantity));
			}
			else
			{
				QuantityText = FText::GetEmpty();
			}

			SlotItemNum->SetText(QuantityText);
			//UE_LOG(LogTemp, Warning, TEXT("number Updated"));
		}
	}


}


