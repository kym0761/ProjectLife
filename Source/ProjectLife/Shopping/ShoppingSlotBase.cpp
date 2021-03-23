// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingSlotBase.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ShoppingActor.h"
#include "../Item/Item.h"
#include "ConfirmShoppingBase.h"
#include "Blueprint/SlateBlueprintLibrary.h"

void UShoppingSlotBase::NativeConstruct()
{
	Super::NativeConstruct();


}

FReply UShoppingSlotBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{

	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

void UShoppingSlotBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

}

bool UShoppingSlotBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	return false;
}

FReply UShoppingSlotBase::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("ButtonUP"));
	}

	if (ConfirmShoppingClass)
	{
		UConfirmShoppingBase* confirmShopping = CreateWidget<UConfirmShoppingBase>(GetOwningPlayer(), ConfirmShoppingClass);
		if (confirmShopping)
		{
			confirmShopping->AddToViewport();
			//confirmShopping->SetPositionInViewport(USlateBlueprintLibrary::LocalToAbsolute(InGeometry, InMouseEvent.GetScreenSpacePosition()));
			confirmShopping->ItemData = ItemData;

			//if (GEngine)
			//{
			//	FVector2D vec = InMouseEvent.GetScreenSpacePosition();
			//		
			//	//USlateBlueprintLibrary::LocalToAbsolute(InGeometry, InMouseEvent.GetScreenSpacePosition());
			//	FString str = vec.ToString();
			//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, str);
			//}

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

void UShoppingSlotBase::InitShoppingSlot(AShoppingActor* ShopOwner, int32 Index)
{
	if (ShopOwner && ShopOwner->Items.IsValidIndex(Index))
	{
		AItem* item = ShopOwner->Items[Index].GetDefaultObject();
		if (item)
		{
			FItemDataStruct itemData = item->ItemData;
			SlotImage->SetBrushFromTexture(itemData.Thumbnail);
			SlotItemName->SetText(FText::FromString(itemData.Name));
			FString priceText = FString::FromInt(itemData.ItemPrice) + FString("$");
			SlotItemPrice->SetText(FText::FromString(priceText));

			ItemData = itemData;
			UE_LOG(LogTemp, Warning, TEXT("Shopping Slot Data's Name : %s"),*ItemData.Name);
		}
	}
}
