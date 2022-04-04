// Fill out your copyright notice in the Description page of Project Settings.


#include "CookWidget.h"
#include "../Inventory/ItemSlot.h"
#include "CookActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "CookSelectionSlot.h"

void UCookWidget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int32 i = 0; i < 5; i++)
	{
		FString slotName = FString("ItemSlot_") + FString::FromInt(i);
		UItemSlot* slot = Cast<UItemSlot>(GetWidgetFromName(FName(*slotName)));
		ItemSlotArray.Add(slot);
	}

	if (IsValid(Button_DoCooking))
	{
		Button_DoCooking->OnClicked.AddDynamic(this, &UCookWidget::Clicked_DoCooking);
	}

}

void UCookWidget::NativeDestruct()
{
	//Widget삭제시 델리게이트 바인드를 제거

	UInventoryComponent* inventoryComponent = CookActorRef->FindComponentByClass<UInventoryComponent>();

	if (IsValid(inventoryComponent))
	{
		inventoryComponent->OnInventoryDataChanged.RemoveDynamic(this, &UCookWidget::UpdateCookWidget);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Warning : Called NativeDestruct()"));

	Super::NativeDestruct();
}

void UCookWidget::InitCookWidget()
{

	if (!IsValid(CookActorRef))
	{
		//failed.
		return;
	}

	UInventoryComponent* inventoryComponent = CookActorRef->FindComponentByClass<UInventoryComponent>();

	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->InventoryComponentRef = inventoryComponent;
		ItemSlotArray[i]->InventorySlotNumber = i;
	}

	ItemSlot_Result->InventoryComponentRef = inventoryComponent;
	ItemSlot_Result->InventorySlotNumber = 10;

	UpdateCookWidget();

	inventoryComponent->OnInventoryDataChanged.AddDynamic(this , &UCookWidget::UpdateCookWidget);
}

void UCookWidget::UpdateCookWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateItemSlot();
	}

	ItemSlot_Result->UpdateItemSlot();

	UpdateSelections();
}

void UCookWidget::Clicked_DoCooking()
{
	if (!IsValid(CookActorRef))
	{
		//failed.
		return;
	}

	bool bSucceed = CookActorRef->MakeCooking(CookResultName);

	if (bSucceed)
	{
		UpdateCookWidget();
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Warning : CookFailed in Clicked_DoCooking()"));
	//}

}

void UCookWidget::UpdateSelections()
{
	VerticalBox_CanDo->ClearChildren();
	CookResultName = FString("");

	if (!IsValid(CookActorRef))
	{
		//failed.
		return;
	}

	if (!IsValid(CookSelectionSlotClass))
	{
		//failed.
		return;
	}

	TArray<FItemRecipeData> list = CookActorRef->CanMakeList();

	for (FItemRecipeData i : list)
	{
		UCookSelectionSlot* slot = NewObject<UCookSelectionSlot>(GetOwningPlayer(), CookSelectionSlotClass);
		VerticalBox_CanDo->AddChild(slot);
		slot->InitCookSelectionSlot(this, i);
	} 

	UE_LOG(LogTemp, Warning, TEXT("Warning : UpdateSelections()"));
}
