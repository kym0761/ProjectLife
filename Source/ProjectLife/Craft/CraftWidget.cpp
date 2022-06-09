// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftWidget.h"
#include "../Inventory/ItemSlot.h"
#include "CraftActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "CraftSelectionSlot.h"


void UCraftWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 5; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

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

	//UE_LOG(LogTemp, Warning, TEXT("Warning : Called NativeDestruct()"));

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

	UInventoryComponent* inventoryComponent = CraftActorRef->FindComponentByClass<UInventoryComponent>();

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventoryComponentRef = inventoryComponent;
		ItemSlotArray[i]->InventorySlotNumber = i;
	}

	ItemSlot_Result->InventoryComponentRef = inventoryComponent;
	ItemSlot_Result->InventorySlotNumber = 10;

	UpdateCraftWidget();

	inventoryComponent->OnInventoryDataChanged.AddDynamic(this, &UCraftWidget::UpdateCraftWidget);
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
	//CookResultName의 값을 보내서 CookActor가 요리를 하도록 요청

	if (!IsValid(CraftActorRef))
	{
		//failed.
		return;
	}

	bool bSucceed = CraftActorRef->Crafting(CraftResultName);

	if (bSucceed)
	{
		UpdateCraftWidget();
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Warning : CookFailed in Clicked_DoCooking()"));
	//}
}

void UCraftWidget::UpdateSelections()
{
	//제조 가능한 아이템의 목록을 출력함
	//CraftActor의 인벤토리에 접근해서 가능한 요리를 찾아야하므로 CraftActor에서 목록을 받아와서 처리


	//Init : Clear
	VerticalBox_CanDo->ClearChildren();
	CraftResultName = FString("");

	if (!IsValid(CraftActorRef))
	{
		//Ref failed.
		return;
	}

	if (!IsValid(CraftSelectionSlotClass))
	{
		//failed.
		return;
	}

	TArray<FItemRecipeData> list = CraftActorRef->GetCanMakeList();

	for (FItemRecipeData i : list)
	{
		UCraftSelectionSlot* slot = NewObject<UCraftSelectionSlot>(GetOwningPlayer(), CraftSelectionSlotClass);
		VerticalBox_CanDo->AddChild(slot);
		slot->InitCraftSelectionSlot(this, i);
	}

	UE_LOG(LogTemp, Warning, TEXT("Warning : UpdateSelections()"));
}

void UCraftWidget::SetCraftResultName(FString InVal)
{
	CraftResultName = InVal;
}
