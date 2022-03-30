// Fill out your copyright notice in the Description page of Project Settings.


#include "CookWidget.h"
#include "../Inventory/ItemSlot.h"
#include "CookActor.h"
#include "../Inventory/InventoryComponent.h"
#include "Components/Button.h"

void UCookWidget::NativeConstruct()
{

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
}

void UCookWidget::UpdateCookWidget()
{
	for (int32 i = 0; i < ItemSlotArray.Num(); i++)
	{
		ItemSlotArray[i]->UpdateItemSlot();
	}

	ItemSlot_Result->UpdateItemSlot();
}

void UCookWidget::Clicked_DoCooking()
{
	if (!IsValid(CookActorRef))
	{
		//failed.
		return;
	}

	bool bSucceed = CookActorRef->MakeCooking();

	if (bSucceed)
	{
		UpdateCookWidget();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Warning : CookFailed in Clicked_DoCooking()"));
	}

}
