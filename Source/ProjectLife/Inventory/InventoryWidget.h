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

	////만약 ItemSlot을 코드 상에서 Spawn할 예정이라면, 그리드 패널에 접근할 필요가 있으므로 아직 삭제하지 말 것.
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
	//	UUniformGridPanel* GridPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Widget")
		TArray<UItemSlot*> ItemSlotArray;

	virtual void NativeConstruct() override;

	void InitInventoryWidget();

	UFUNCTION()
	void UpdateInventoryWidget();

protected:

	virtual bool Initialize() override;

	virtual void NativePreConstruct() override;
};
