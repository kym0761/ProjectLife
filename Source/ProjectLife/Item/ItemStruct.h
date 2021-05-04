// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "../Base/AttackStruct.h"
#include "ItemStruct.Generated.h"

class AItem;
class ABasicWeapon;

UENUM(BlueprintType)
enum class EItemType: uint8
{
	None UMETA(DisplayName = "None"),
	Consumption UMETA(DisplayName = "Consumption"),
	Equipment UMETA(DisplayName = "Equipment"),
	Resource UMETA(DisplayName = "Resource")
};

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	Normal UMETA(DisplayName = "Normal"),
	Rare UMETA(DisplayName = "Rare"),
	Unique UMETA(DisplayName = "Unique"),
	Epic UMETA(DisplayName = "Epic")
};

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	None UMETA(DisplayName = "None"),
	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory UMETA(DisplayName = "Accessory")
};

//Using In Equipment Function.
UENUM(BlueprintType)
enum class EEquipmentSlot : uint8
{
	None UMETA(DisplayName = "None"),
	Weapon UMETA(DisplayName = "Weapon"),
	Shield UMETA(DisplayName = "Shield"),
	Armor UMETA(DisplayName = "Armor"),
	Accessory1 UMETA(DisplayName = "Accessory1"),
	Accessory2 UMETA(DisplayName = "Accessory2")
};

//USTRUCT(BlueprintType)
//struct FItemDataStruct : public FTableRowBase
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		FString Name;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		UTexture2D* Thumbnail;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		FString Description;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		bool bIsStackable;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		int32 Quantity;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		int32 MaxQuantity;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		TSubclassOf<AItem> ItemClass;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		EItemType ItemType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		EItemRarity ItemRarity;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
//		int32 ItemPrice;
//	
//	/*Equipment*/
//	
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
//		float Attack;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
//		float Defense;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
//		float CriticalHit;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
//		EEquipmentType EquipmentType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//		EAttackType AttackType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//		EAttackRangeType AttackRangeType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//		EDamageType DamageType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//		EElement Element;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
//		TSubclassOf<ABasicWeapon> WeaponClass;
//
//
//
//	FItemDataStruct();
//
//};

UCLASS(BlueprintType, Blueprintable, abstract)
class PROJECTLIFE_API UItemData : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		UTexture2D* Thumbnail;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		bool bIsStackable;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	//	int32 Quantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 MaxQuantity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TSubclassOf<AItem> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item") //? Needed?
		EItemType ItemType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		EItemRarity ItemRarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 ItemPrice;

	UItemData();

};

UCLASS(BlueprintType, Blueprintable, abstract)
class PROJECTLIFE_API UConsumableItemData : public UItemData
{
	GENERATED_BODY()

public:

	UConsumableItemData();
};

//UCLASS(BlueprintType, Blueprintable, abstract)
//class PROJECTLIFE_API UWeaponItemData : public UItemData
//{
//	GENERATED_BODY()
//
//public:
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		float Attack;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		float Defense;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		float CriticalHit;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		EEquipmentType EquipmentType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		EAttackType AttackType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		EAttackRangeType AttackRangeType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		EDamageType DamageType;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		EElement Element;
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
//		TSubclassOf<ABasicWeapon> WeaponClass;
//
//	UWeaponItemData();
//};

UCLASS(BlueprintType, Blueprintable, abstract)
class PROJECTLIFE_API UEquipmentItemData : public UItemData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		float Attack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		float Defense;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		float CriticalHit;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		EEquipmentType EquipmentType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		EAttackType AttackType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		EAttackRangeType AttackRangeType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		EDamageType DamageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		EElement Element;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Weapon")
		TSubclassOf<ABasicWeapon> WeaponClass;

	UEquipmentItemData();
};

USTRUCT(BlueprintType)
struct FItemDataSlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		TSubclassOf<UItemData> ItemData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		int32 Quantity;

	FItemDataSlot();
};