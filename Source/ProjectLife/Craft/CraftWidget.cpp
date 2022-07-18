// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWidget.h"
#include "Inventory/ItemSlot.h"
#include "CraftActor.h"
#include "Inventory/InventoryComponent.h"
#include "CraftComponent.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "CraftSelectionSlot.h"
#include "Components/ProgressBar.h"

void UCraftWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 5; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	//버튼 기능 Bind
	if (IsValid(Button_DoCrafting))
	{
		Button_DoCrafting->OnClicked.AddDynamic(this, &UCraftWidget::Clicked_DoCrafting);
	}
}

void UCraftWidget::NativeDestruct()
{
	//Widget삭제시 델리게이트 바인드를 제거
	UInventoryComponent* inventoryComponent = CraftActorRef->FindComponentByClass<UInventoryComponent>();
	if (IsValid(inventoryComponent))
	{
		inventoryComponent->OnInventoryDataChanged.RemoveDynamic(this, &UCraftWidget::UpdateCraftWidget);
	}

	CraftActorRef->CraftComponent->OnCrafting.RemoveDynamic(this, &UCraftWidget::SetProgress);

	Super::NativeDestruct();
}

void UCraftWidget::InitCraftWidget(ACraftActor* CraftActor)
{
	if (!IsValid(CraftActor))
	{
		//Input failed.
		return;
	}

	CraftActorRef = CraftActor;

	if (!IsValid(CraftActorRef))
	{
		//Ref failed.
		return;
	}

	//CraftActor의 인벤토리에 접근하고, itemSlotArray에 인벤토리와 Bind...총 5개
	UInventoryComponent* inventoryComponent = CraftActorRef->FindComponentByClass<UInventoryComponent>();

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventoryComponentRef = inventoryComponent;
		ItemSlotArray[i]->InventorySlotNumber = i;
	}

	//Craft 결과가 나오는 슬롯과 인벤토리 Bind...10번째 위치
	ItemSlot_Result->InventoryComponentRef = inventoryComponent;
	ItemSlot_Result->InventorySlotNumber = 10;

	UpdateCraftWidget();

	//Inventory 값이 변경되면 자동으로 Inventory Slot의 업데이트를 위해 델리게이트에 Bind함.
	inventoryComponent->OnInventoryDataChanged.AddDynamic(this, &UCraftWidget::UpdateCraftWidget);
	CraftActorRef->CraftComponent->OnCrafting.AddDynamic(this, &UCraftWidget::SetProgress);
}

void UCraftWidget::UpdateCraftWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateItemSlot();
	}

	ItemSlot_Result->UpdateItemSlot();

	UpdateSelections();
}

void UCraftWidget::Clicked_DoCrafting()
{
	//CraftResultName의 값을 보내서 CraftActor가 제작을 하도록 요청

	if (!IsValid(CraftActorRef))
	{
		//failed.
		return;
	}

	//Craft Actor에게 제작 요청
	CraftActorRef->RequestCrafting(CraftResultName);

}

void UCraftWidget::UpdateSelections()
{
	//제조 가능한 아이템의 목록을 출력함
	//CraftActor의 인벤토리에 접근해서 가능한 요리를 찾아야하므로 CraftActor에서 목록을 받아와서 처리

	//기존의 만들 수 있던 아이템 목록을 전부 Clear
	VerticalBox_CanDo->ClearChildren();

	if (!IsValid(CraftActorRef))
	{
		//Ref failed.
		return;
	}

	if (!IsValid(CraftActorRef->CraftComponent))
	{
		//Craft Comp Ref failed.
		return;
	}

	if (!IsValid(CraftSelectionSlotClass))
	{
		//failed.
		return;
	}

	//만들 수 있는 아이템 목록
	TArray<FItemRecipeData> list = CraftActorRef->CraftComponent->GetCanMakeList();

	//CraftResultName을 초기화해야 하는지 확인.
	bool bClearResultName = true;

	for (FItemRecipeData i : list)
	{
		UCraftSelectionSlot* slot = NewObject<UCraftSelectionSlot>(GetOwningPlayer(), CraftSelectionSlotClass);
		VerticalBox_CanDo->AddChild(slot);
		slot->InitCraftSelectionSlot(this, i);


		if (i.ItemName == CraftResultName) // 기존에 만들었던 것 발견.
		{
			bClearResultName = false;
		}

	}

	//초기화 할 필요 있다면 초기화.
	if (bClearResultName)
	{
		if (VerticalBox_CanDo->HasAnyChildren())
		{
			UCraftSelectionSlot* slot = Cast<UCraftSelectionSlot>(VerticalBox_CanDo->GetChildAt(0));
			if (IsValid(slot))
			{
				CraftResultName = slot->GetItemName();
			}
			else
			{
				CraftResultName = FString("");
			}
		}
		else
		{
			CraftResultName = FString("");
		}
	}

}

void UCraftWidget::SetCraftResultName(FString InVal)
{
	CraftResultName = InVal;
}

void UCraftWidget::SetProgress(float InVal)
{
	if (!IsValid(ProgressBar_Crafting))
	{
		return;
	}

	//InVal은 0.0f ~ 1.0f 값으로, 이미 감안하고 Parameter로 들어오므로 상관할 필요는 없을 것.
	ProgressBar_Crafting->SetPercent(InVal);
}
