// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Item/ItemStruct.h"
#include "CookSelectionSlot.generated.h"

class UImage;
class UTextBlock;
class UCookWidget;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UCookSelectionSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UImage* Image_SlotImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* TextBlock_SlotItemName;

private:

	//���� ���ý� ������ ������ �ҷ��� �� �ֵ��� ������ �̸��� ������.
	UPROPERTY()
		FString ItemNameText;

	UPROPERTY()
		UCookWidget* ParentCookWidgetRef;

public:

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void InitCookSelectionSlot(UCookWidget* ParentCookWidget, FItemRecipeData RecipeData);

	void SetCookWidgetSelection();
};
