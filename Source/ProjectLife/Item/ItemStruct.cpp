// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStruct.h"

FItemDataStruct::FItemDataStruct()
{
    Name = FString("");
    Thumbnail = nullptr;
    Description = FString("");
	bIsStackable = false;
    Quantity = 0;
    MaxQuantity = 1;
    ItemClass = nullptr;
    ItemType = EItemType::None;
	WeaponClass = nullptr;
	ItemRarity = EItemRarity::Normal;
	ItemPrice = 0;
	Attack = 0.0f;
	Defense = 0.0f;
	CriticalHit = 0.0f;
	EquipmentType = EEquipmentType::None;
	AttackType = EAttackType::None;
	AttackRangeType = EAttackRangeType::None;
	Element = EElement::None;
	DamageType = EDamageType::None;
}