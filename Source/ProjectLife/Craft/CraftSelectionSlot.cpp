// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftSelectionSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "../GamePlay/ProjectLIfeGameInstance.h"
#include "CraftWidget.h"

void UCraftSelectionSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

FReply UCraftSelectionSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	return FReply::Handled();
}

FReply UCraftSelectionSlot::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);

	SetCraftWidgetSelection();

	return FReply::Handled();
}

void UCraftSelectionSlot::InitCraftSelectionSlot(UCraftWidget* ParentCraftWidget, FItemRecipeData RecipeData)
{
	ParentCraftWidgetRef = ParentCraftWidget;

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

void UCraftSelectionSlot::SetCraftWidgetSelection()
{
	if (!IsValid(ParentCraftWidgetRef))
	{
		return;
	}

	//CraftWidget의 선택된 레시피의 아이템 이름
	ParentCraftWidgetRef->SetCraftResultName(ItemNameText);
}
