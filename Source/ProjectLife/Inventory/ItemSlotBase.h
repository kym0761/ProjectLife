// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlotBase.generated.h"

class UImage;
class UTextBlock;
class UInventoryComponent;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UItemSlotBase : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UImage* SlotImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SlotItemNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 InventoryIndex;

	//UI's Owner's Inventory.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		UInventoryComponent* InventoryRef;

	//Using for Drag Drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UItemSlotBase> ItemSlotClass;

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

	void UpdateSlot();
};
