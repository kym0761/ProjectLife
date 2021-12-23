// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStruct.h"

FItemData::FItemData()
{
	Name = FString("");
	Thumbnail = nullptr;
	Description = FString("");
	bIsStackable = false;
	//Quantity = 0;
	MaxQuantity = 1;
	ItemClass = nullptr;
	ItemType = EItemType::None;
	ItemRarity = EItemRarity::Normal;
	ItemPrice = 0;
	ItemMesh = nullptr;
}

FItemDataSlot::FItemDataSlot()
{
	Quantity = 0;
}

FEquipmentItemData::FEquipmentItemData()
{
	Name = FString("");
	Attack = 0.0f;
	Defense = 0.0f;
	CriticalHit = 0.0f;
	EquipmentType = EEquipmentType::None;
	AttackType = EGameAttackType::None;
	AttackRangeType = EGameAttackRangeType::None;
	ElementType = EGameElementType::None;
	DamageType = EGameDamageType::None;
	WeaponClass = nullptr;
}

FConsumableItemData::FConsumableItemData()
{
	Name = FString("");
}

FShopItemData::FShopItemData()
{
	ItemName = FString();
	bLimited = false;
	Quantity = 1;
}
