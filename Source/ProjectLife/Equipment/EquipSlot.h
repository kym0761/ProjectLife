// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Blueprint/UserWidget.h"
#include "EquipSlot.generated.h"

class UImage;
class UEquipmentComponent;


/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UEquipSlot : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (BindWidget))
		UImage* SlotImage;
	
	//Set Equipment Slot Type
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		EEquipmentSlot EquipmentSlot;

	//Set What Type is Available
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		EEquipmentType EquipmentType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UEquipSlot> EquipSlotClass;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		UEquipmentComponent* EquipmentCompRef;

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

	void UpdateEquipSlot();

	void SetEquipmentCompRef(UEquipmentComponent* InVal);
	UEquipmentComponent* GetEquipmentCompRef() const;
};
