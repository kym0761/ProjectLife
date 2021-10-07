// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UUniformGridPanel;
class UItemSlot;
class UEquipSlot;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	//if Spawn ItemSlot Dynamically, Use it. so don't Delete yet.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	//	UUniformGridPanel* GridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		TArray<UItemSlot*> ItemSlotArray;

	virtual void NativeConstruct() override;

	void InitInventoryWidget();

	void UpdateInventoryWidget();
};
