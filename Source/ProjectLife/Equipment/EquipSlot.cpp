// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipSlot.h"
#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "../Inventory/ItemSlot.h"
#include "EquipmentComponent.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Base/BasicPlayerController.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Inventory/InventoryComponent.h"

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
	// ////ENUM PRINT CODE
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

	if (!IsValid(EquipmentCompRef))
	{
		return;
	}

	//Make New Equip Slot For Drag.
	//current
	FEquipmentItemData equipmentItemData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);

	if (equipmentItemData.IsEmpty())
	{
		return;
	}

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	FItemData itemData;
	if (IsValid(gameInstance))
	{
		itemData = gameInstance->GetItemDataFromTable(equipmentItemData.Name);
	}
	else
	{
		return;
	}

	if (!IsValid(EquipSlotClass))
	{
		UE_LOG(LogTemp, Warning, TEXT("EquipSlotClass is not Exist. Set Equip Class First."));
	}


	UEquipSlot* dragDisplay = CreateWidget<UEquipSlot>(GetOwningPlayer(), EquipSlotClass);
	if (IsValid(dragDisplay))
	{
		if (IsValid(itemData.Thumbnail))
		{
			dragDisplay->SlotImage->SetBrushFromTexture(itemData.Thumbnail);
		}

		UDragDropOperation* dragDropOper = NewObject<UDragDropOperation>();
		dragDropOper->Payload = this;
		dragDropOper->DefaultDragVisual = dragDisplay;
		dragDropOper->Pivot = EDragPivot::CenterCenter;

		OutOperation = dragDropOper;
	}
	



}

bool UEquipSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (!IsValid(InOperation))
	{
		return false;
	}

	//if a dropped slot is a Item Slot
	//Get ItemData And Equip it if it is EquipmentData.
	{
		UItemSlot* droppedItemSlot = Cast<UItemSlot>(InOperation->Payload);
		if (IsValid(droppedItemSlot))
		{
			//drop의 인벤토리 정보를 받아옴.
			int32 drop_InventorySlotNumber = droppedItemSlot->InventorySlotNumber;
			UInventoryComponent* drop_InventoryComponent = droppedItemSlot->InventoryComponentRef;
			if (!IsValid(drop_InventoryComponent))
			{
				//inventory Component Failed
				UE_LOG(LogTemp, Warning, TEXT("inventory Component Failed"));
				return false;
			}

			FItemDataSlot itemDataSlot = drop_InventoryComponent->GetInventoryItem(drop_InventorySlotNumber);
			UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());
			if (!IsValid(gameInstance))
			{
				UE_LOG(LogTemp, Warning, TEXT("GameInstance Failed"));
				return false;
			}

			//인벤토리 데이터를 아이템 데이터로 변환.
			FItemData itemData = gameInstance->GetItemDataFromTable(itemDataSlot.ItemName);
			if (itemData.ItemType == EItemType::Equipment)
			{
				FEquipmentItemData equipmentItemData = gameInstance->GetEquipmentItemDataFromTable(itemData.Name);

				if (equipmentItemData.EquipmentType == EquipmentType)
				{
					FEquipmentItemData currentEquipment = EquipmentCompRef->GetEquipmentData(EquipmentSlot);
					bool bSucceed = EquipmentCompRef->SetEquipment(EquipmentSlot, equipmentItemData);
					if (bSucceed)
					{
						FItemDataSlot temp;
						temp.ItemName = currentEquipment.Name;
						temp.Quantity = temp.ItemName != FString("") ? 1 : 0;

						drop_InventoryComponent->SetInventoryItem(drop_InventorySlotNumber, temp);

						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							//playerController->UpdateInventory();
							playerController->UpdateEquipment();
							return true;
						}
					}
				}
			}
		}
	}

	//if drop is Equip slot. Maybe Accessory? ex) accessory1 <->accessory2 swap.
	//other Equipment Slot Will not Valid.. because there is no other Weapon Slot or Armor slot, etc... in game...
	{
		UEquipSlot* droppedEquipSlot = Cast<UEquipSlot>(InOperation->Payload);
		if (IsValid(droppedEquipSlot))
		{
			if (IsValid(droppedEquipSlot->EquipmentCompRef) && IsValid(EquipmentCompRef) && (EquipmentType == droppedEquipSlot->EquipmentType) && (EquipmentSlot != droppedEquipSlot->EquipmentSlot))
			{
				FEquipmentItemData CurrentEquipmentData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);
				FEquipmentItemData droppedEquipmentData = droppedEquipSlot->EquipmentCompRef->GetEquipmentData(droppedEquipSlot->EquipmentSlot);

				droppedEquipSlot->EquipmentCompRef->SetEquipment(droppedEquipSlot->EquipmentSlot, CurrentEquipmentData);
				EquipmentCompRef->SetEquipment(EquipmentSlot, droppedEquipmentData);

				ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
				if (playerController)
				{
					//playerController->UpdateInventory();
					playerController->UpdateEquipment();
					return true;
				}
			}
		}
	}

	return false;
}

void UEquipSlot::UpdateEquipSlot()
{
	//Update Slot with Current Data.

	if (IsValid(EquipmentCompRef))
	{
		FEquipmentItemData equipmentItemData = EquipmentCompRef->GetEquipmentData(EquipmentSlot);
		

		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		FItemData itemData;
		if (IsValid(gameInstance))
		{
			itemData = gameInstance->GetItemDataFromTable(equipmentItemData.Name);
			UE_LOG(LogTemp, Warning, TEXT("Get Item Data.."));
		}

		if (IsValid(SlotImage) && IsValid(itemData.Thumbnail))//Set Image
		{
			SlotImage->SetBrushFromTexture(itemData.Thumbnail);
			UE_LOG(LogTemp, Warning, TEXT("Image Updated"));
		}
		else //empty
		{
			SlotImage->SetBrushFromTexture(nullptr);
		}
	}
}
