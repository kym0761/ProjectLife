// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ShoppingSlotBase.generated.h"

class UImage;
class UTextBlock;
class AShoppingActor;
class UConfirmShoppingBase;
/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UShoppingSlotBase : public UUserWidget
{
	GENERATED_BODY()
public:
	
	UPROPERTY(Meta = (BindWidget))
		UImage* SlotImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SlotItemName;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SlotItemPrice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		FItemDataSlot ItemDataSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button")
		TSubclassOf<UConfirmShoppingBase> ConfirmShoppingClass;

	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry,
		const FPointerEvent& InMouseEvent,
		UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry,
		const FDragDropEvent& InDragDropEvent,
		UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void InitShoppingSlot(AShoppingActor* ShopOwner, int32 Index);
};
