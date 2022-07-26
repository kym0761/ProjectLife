// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

class UEquipSlot;

/**
 * 
 */
UCLASS()
class PROJECTLIFE_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UPROPERTY(Meta = (BindWidget))
		UEquipSlot* WeaponSlot;

	UPROPERTY(Meta = (BindWidget))
		UEquipSlot* ArmorSlot;

	UPROPERTY(Meta = (BindWidget))
		UEquipSlot* ShieldSlot;

	UPROPERTY(Meta = (BindWidget))
		UEquipSlot* Accessory1Slot;

	UPROPERTY(Meta = (BindWidget))
		UEquipSlot* Accessory2Slot;

public:

	virtual void NativeConstruct() override;

	void InitEquipmentWidget();

	void UpdateEquipmentWidget();

protected:

	virtual bool Initialize() override;
};
