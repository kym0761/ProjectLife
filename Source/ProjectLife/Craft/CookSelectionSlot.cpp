// Fill out your copyright notice in the Description page of Project Settings.


#include "CookSelectionSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../ProjectLIfeGameInstance.h"
#include "CookWidget.h"

void UCookSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply UCookSelectionSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UCookSelectionSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry,InMouseEvent);

	SetCookWidgetSelection();

	return FReply::Handled();
}

void UCookSelectionSlot::InitCookSelectionSlot(UCookWidget* ParentCookWidget, FItemRecipeData RecipeData)
{
	ParentCookWidgetRef = ParentCookWidget;

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(GetGameInstance());

	if (!IsValid(gameInstance))
	{
		return;
	}

	//인벤토리 데이터를 아이템 데이터로 변환.
	FItemData itemData = gameInstance->GetItemDataFromTable(RecipeData.ItemName);

	if (IsValid(Image_SlotImage))//Set Image
	{
		if (IsValid(itemData.Thumbnail))
		{
			Image_SlotImage->SetBrushFromTexture(itemData.Thumbnail);
		}
		else
		{
			Image_SlotImage->SetBrushFromTexture(nullptr);
		}
	}

	if (IsValid(TextBlock_SlotItemName))//Set Image
	{
		ItemNameText = itemData.Name;

		TextBlock_SlotItemName->SetText(FText::FromString(ItemNameText));
	}


}

void UCookSelectionSlot::SetCookWidgetSelection()
{
	if (!IsValid(ParentCookWidgetRef))
	{
		return;
	}

	ParentCookWidgetRef->SetCookResultName(ItemNameText);


}
