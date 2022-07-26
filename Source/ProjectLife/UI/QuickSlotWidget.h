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

private:

	UPROPERTY()
		TArray<UItemSlot*> QuickSlotArray;

public:

	virtual void NativeConstruct() override;

	void InitQuickSlot();

	UFUNCTION()
	void UpdateQuickSlot();

protected:

	virtual bool Initialize() override;

};
