// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "ShoppingActor.h"
#include "ConfirmShopping.h"
#include "Blueprint/SlateBlueprintLibrary.h"



void UShoppingSlot::NativeConstruct()
{
	Super::NativeConstruct();

	ShopOwnerRef = nullptr;
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

	//if (GEngine)
	//{
	//	GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Green, TEXT("ButtonUP"));
	//}

	if (IsValid(ConfirmShoppingClass))
	{
		UConfirmShopping* confirmShopping = CreateWidget<UConfirmShopping>(GetOwningPlayer(), ConfirmShoppingClass);
		if (IsValid(confirmShopping))
		{
			confirmShopping->InitConfirmShopping(ShopOwnerRef, ItemIndex);
			confirmShopping->AddToViewport();
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
	if (IsValid(ShopOwner) && ShopOwner->Items.IsValidIndex(Index))
	{
		FItemData itemData = ShopOwner->Items[Index];

		if (IsValid(SlotImage) && IsValid(itemData.Thumbnail))
		{
			SlotImage->SetBrushFromTexture(itemData.Thumbnail);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FAILED"));
		}
			
		if (IsValid(SlotItemName))
		{
			SlotItemName->SetText(FText::FromString(itemData.Name));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FAILED"));
		}

		if (IsValid(SlotItemPrice))
		{
			FString priceText = FString::FromInt(itemData.ItemPrice) + FString("$");
			SlotItemPrice->SetText(FText::FromString(priceText));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FAILED"));
		}

		ItemIndex = Index;
		ShopOwnerRef = ShopOwner;
	}
}
