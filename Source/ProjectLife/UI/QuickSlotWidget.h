// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuickSlotWidget.generated.h"

class UHorizontalBox;
class ABasicCharacter;
class UItemSlot;

/**
 * 
 */
UCLASS(abstract)
class PROJECTLIFE_API UQuickSlotWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(Meta = (BindWidget))
		UHorizontalBox* QuickSlotBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "QuickSlot")
		TArray<UItemSlot*> ItemSlotArray;

	virtual void NativeConstruct() override;

	void InitQuickSlot();

	void UpdateQuickSlot();
};
