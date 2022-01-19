// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Item/Item.h"
#include "../Base/BasicCharacter.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../Base/BasicPlayerController.h"
#include "../Equipment/EquipSlot.h"
#include "../Equipment/EquipmentComponent.h"

#include "../ProjectLIfeGameInstance.h"
#include "InventoryManager.h"
#include "Kismet/GameplayStatics.h"
//#include "Kismet/KismetInputLibrary.h"
//#include "Blueprint/SlateBlueprintLibrary.h"



void UItemSlot::NativeConstruct()
{
	Super::NativeConstruct();
	
	SetVisibility(ESlateVisibility::Visible);
	InitItemSlot();
}

FReply UItemSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry,InMouseEvent);

	//Drag Function Activate.
	FEventReply reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	
	return reply.NativeReply;
}

void UItemSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry,InMouseEvent,OutOperation);

	if (!IsValid(InventoryManagerRef))
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryRef is not Exist..."));
		return;
	}

	if (!InventoryManagerRef->Inventories.Contains(InventoryNumber))
	{
		return;
	}

	if (!InventoryManagerRef->Inventories[0]->Items.IsValidIndex(InventorySlotNumber))
	{
		return;
	}

	FItemDataSlot itemSlotData = InventoryManagerRef->GetInventoryItem(InventoryNumber, InventorySlotNumber);

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());
	if (IsValid(gameInstance))
	{
		FItemData itemData = gameInstance->GetItemDataFromTable(itemSlotData.ItemName);

		//Todo : change to is empty?
		if (itemData == FItemData())
		{
			return;
		}

		if (IsValid(ItemSlotClass))
		{
			//Create DragDisplayUI
			UItemSlot* dragDisplay = CreateWidget<UItemSlot>(GetOwningPlayer(), ItemSlotClass);

			if (IsValid(dragDisplay))
			{
				dragDisplay->InventoryManagerRef = InventoryManagerRef;
				dragDisplay->InventoryNumber = InventoryNumber;
				dragDisplay->InventorySlotNumber = InventorySlotNumber;

				//Set Default Image and Number.
				if (IsValid(itemData.Thumbnail))
				{
					dragDisplay->SlotImage->SetBrushFromTexture(itemData.Thumbnail);
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
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("ItemSlotClass is not Exist. Add Slot Class Please."));
		}
	}
	
}

bool UItemSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	//check InOperation is Existed.
	if (InOperation)
	{
		/*ItemSlot*/
		{
			//Get Payload and Cast To ItemSlot.
			UItemSlot* droppedItemSlot = Cast<UItemSlot>(InOperation->Payload);

			if (IsValid(droppedItemSlot)) //Get InventoryRef & Index.
			{
				//drop의 인벤토리 정보를 받아옴.
				int32 drop_InventoryNumber = droppedItemSlot->InventoryNumber;
				int32 drop_InventorySlotNumber = droppedItemSlot->InventorySlotNumber;
				AInventoryManager* drop_InventoryManager = droppedItemSlot->InventoryManagerRef;

				if (IsValid(drop_InventoryManager) && IsValid(InventoryManagerRef))
				{
					//drop과 정보 교체
					bool bSucceed = InventoryManagerRef->SwapItemBetweenInventory(drop_InventoryNumber, drop_InventorySlotNumber, InventoryNumber, InventorySlotNumber);
				
					if (bSucceed)
					{
						//인벤토리 업데이트
						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							//UE_LOG(LogTemp,Warning,TEXT("Attempt Update Inventory"));
							playerController->UpdateInventory();
							return true;
						}
					}
				}
			}
		}


		/*EquipSlot, similar With [Item Slot] code*/
		{
			UEquipSlot* droppedEquipSlot = Cast<UEquipSlot>(InOperation->Payload);
			if (IsValid(droppedEquipSlot))
			{
				UEquipmentComponent* equipmentComp = droppedEquipSlot->EquipmentCompRef;
				EEquipmentSlot droppedEquipmentslot = droppedEquipSlot->EquipmentSlot;

				if (IsValid(equipmentComp))
				{
					bool bSucceed = equipmentComp->SwapWithInventory(droppedEquipmentslot, InventoryNumber, InventorySlotNumber);
					if (bSucceed)
					{
						UE_LOG(LogTemp, Warning, TEXT("swap inventory - equip OK? "));

						ABasicPlayerController* playerController = Cast<ABasicPlayerController>(GetOwningPlayer());
						if (playerController)
						{
							//UE_LOG(LogTemp, Warning, TEXT("Attempt Update Equipment"));
							playerController->UpdateInventory();
							playerController->UpdateEquipment();
							return true;
						}
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("swap inventory - equip NO? "));
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("InOperation in ItemSlot is NULL."));
	}


	return false;
}

FReply UItemSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	//TODO : 인벤토리 아이템 사용 기능부터 추가해야함.

	//if (IsValid(InventoryManagerRef))
	//{
	//	bool bSucceed = InventoryRef->UseItemInInventory(InventoryIndex);
	//	if (bSucceed)
	//	{
	//		UpdateSlot();

	//		if (GEngine)
	//		{
	//			GEngine->AddOnScreenDebugMessage((int32)FMath::Rand(), 5.0f, FColor::Turquoise, TEXT("Using Item in your Inventory"));
	//		}
	//	}
	//}

	return FReply::Handled();
}

void UItemSlot::InitItemSlot()
{
	AInventoryManager* inventoryManager = Cast<AInventoryManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AInventoryManager::StaticClass()));

	if (IsValid(inventoryManager))
	{
		InventoryManagerRef = inventoryManager;
		//Player Inventory Number.
		InventoryNumber = 0;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Sequence is not right."));
	}

	UpdateItemSlot();
}

void UItemSlot::UpdateItemSlot()
{
	// Update Slot with Current Inventory Infomation.

	if (!IsValid(InventoryManagerRef))
	{
		return;
	}

	if (!InventoryManagerRef->Inventories.Contains(InventoryNumber))
	{
		return;
	}

	if (!InventoryManagerRef->Inventories[InventoryNumber]->Items.IsValidIndex(InventorySlotNumber))
	{
		return;
	}

	//인벤토리 데이터를 가져옴
	FItemDataSlot itemSlotData = InventoryManagerRef->Inventories[0]->Items[InventorySlotNumber];
	
	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());
	if (IsValid(gameInstance))
	{
		//인벤토리 데이터를 아이템 데이터로 변환.
		FItemData itemData = gameInstance->GetItemDataFromTable(itemSlotData.ItemName);

		if (IsValid(SlotImage))//Set Image
		{
			if (IsValid(itemData.Thumbnail))
			{
				SlotImage->SetBrushFromTexture(itemData.Thumbnail);
			}
			else
			{
				SlotImage->SetBrushFromTexture(nullptr);
			}
		}

		if (IsValid(SlotItemNum))//Set Number
		{
			FText QuantityText;

			if (itemData.bIsStackable)
			{
				QuantityText = FText::FromString(FString::FromInt(itemSlotData.Quantity));
			}
			else
			{
				QuantityText = FText::GetEmpty();
			}

			SlotItemNum->SetText(QuantityText);
		}
	}
	else // set default
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


