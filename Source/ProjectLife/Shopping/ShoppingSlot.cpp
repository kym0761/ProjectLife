// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ShoppingActor.h"
#include "../Item/Item.h"
#include "ConfirmShopping.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UShoppingSlot::NativeConstruct()
{
	Super::NativeConstruct();


}

FReply UShoppingSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

void UShoppingSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UShoppingSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return false;
}

FReply UShoppingSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("ButtonUP"));
	}

	if (ConfirmShoppingClass)
	{
		UConfirmShopping* confirmShopping = CreateWidget<UConfirmShopping>(GetOwningPlayer(), ConfirmShoppingClass);
		if (confirmShopping)
		{
			confirmShopping->AddToViewport();
			confirmShopping->ItemDataSlot = ItemDataSlot;
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("ConfirmShoppingWidget is Not Exist"));
		}
	}
	return FReply::Handled();
}

void UShoppingSlot::InitShoppingSlot(AShoppingActor* ShopOwner, int32 Index)
{
	if (ShopOwner && ShopOwner->Items.IsValidIndex(Index))
	{

		AItem* item = ShopOwner->Items[Index].GetDefaultObject();
		if (item)
		{
			FItemDataSlot itemDataSlot;// = item->ItemDataSlot;
			
			FItemData itemData = itemDataSlot.ItemData;

			if (IsValid(SlotImage) && IsValid(itemData.Thumbnail))
			{
				SlotImage->SetBrushFromTexture(itemData.Thumbnail);
			}

			if (IsValid(SlotItemName))
			{
				SlotItemName->SetText(FText::FromString(itemData.Name));
			}

			if (IsValid(SlotItemPrice))
			{
				FString priceText = FString::FromInt(itemData.ItemPrice) + FString("$");
				SlotItemPrice->SetText(FText::FromString(priceText));
			}

			ItemDataSlot = itemDataSlot;
				
			
		}
	}
}
