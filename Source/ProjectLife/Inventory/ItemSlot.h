// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "ItemSlot.generated.h"

class UImage;
class UTextBlock;
class UInventoryComponent;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UItemSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(Meta = (BindWidget))
		UImage* SlotImage;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* SlotItemNum;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 InventorySlotNumber;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		UInventoryComponent* InventoryComponentRef;

	//Using for Drag Drop
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UItemSlot> ItemSlotClass;

public:

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

	void InitItemSlot(AActor* HasInventoryComponent);
	void UpdateItemSlot();
};
