// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidgetBase.generated.h"

class UUniformGridPanel;
class UItemSlotBase;
class UEquipSlotBase;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UInventoryWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//if Spawn ItemSlot Dynamically, Use it. so don't Delete yet.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	//	UUniformGridPanel* GridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		TArray<UItemSlotBase*> ItemSlotArray;

	virtual void NativeConstruct() override;

	void InitInventoryWidget();

	void UpdateInventoryWidget();
};
