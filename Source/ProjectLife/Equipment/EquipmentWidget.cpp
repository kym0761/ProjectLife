// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentWidget.h"
#include "EquipmentComponent.h"
#include "EquipSlot.h"

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitEquipmentWidget();
}

void UEquipmentWidget::InitEquipmentWidget()
{

	if (IsValid(GetOwningPlayer()))
	{
		UEquipmentComponent* equipmentComp = GetOwningPlayer()->GetPawn()->FindComponentByClass<UEquipmentComponent>();

		//set Equip Slot's EquipmentComp.
		if (IsValid(equipmentComp))
		{
			WeaponSlot->SetEquipmentCompRef(equipmentComp);
			WeaponSlot->EquipmentSlot = EEquipmentSlot::Weapon;
			WeaponSlot->EquipmentType = EEquipmentType::Weapon;

			ArmorSlot->SetEquipmentCompRef(equipmentComp);
			ArmorSlot->EquipmentSlot = EEquipmentSlot::Armor;
			ArmorSlot->EquipmentType = EEquipmentType::Armor;
			
			ShieldSlot->SetEquipmentCompRef(equipmentComp);
			ShieldSlot->EquipmentSlot = EEquipmentSlot::Shield;
			ShieldSlot->EquipmentType = EEquipmentType::Shield;

			Accessory1Slot->SetEquipmentCompRef(equipmentComp);
			Accessory1Slot->EquipmentSlot = EEquipmentSlot::Accessory1;
			Accessory1Slot->EquipmentType = EEquipmentType::Accessory;

			Accessory2Slot->SetEquipmentCompRef(equipmentComp);
			Accessory2Slot->EquipmentSlot = EEquipmentSlot::Accessory2;
			Accessory2Slot->EquipmentType = EEquipmentType::Accessory;
		}

	}


}

void UEquipmentWidget::UpdateEquipmentWidget()
{
	if (IsValid(WeaponSlot))
	{
		WeaponSlot->UpdateEquipSlot();
	}

	if (IsValid(ArmorSlot))
	{
		ArmorSlot->UpdateEquipSlot();
	}

	if (IsValid(ShieldSlot))
	{
		ShieldSlot->UpdateEquipSlot();
	}

	if (IsValid(Accessory1Slot))
	{
		Accessory1Slot->UpdateEquipSlot();
	}

	if (IsValid(Accessory2Slot))
	{
		Accessory2Slot->UpdateEquipSlot();
	}

	UE_LOG(LogTemp, Warning, TEXT("UpdateEquipmentWidget()"));
}
