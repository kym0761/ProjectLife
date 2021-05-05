// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "InventoryComponent.h"
#include "../Base/StatComponent.h"
#include "../Base/BasicWeapon.h"
#include "../Base/BasicCharacter.h"

// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UEquipmentComponent::SetEquipment(EEquipmentSlot EquipmentSlot, FItemDataSlot InData)
{
	bool bEquipable = false;


	if (IsValid(InData.ItemData))
	{
		UItemData* itemData = InData.ItemData.GetDefaultObject();
		if (IsValid(itemData))
		{

			UEquipmentItemData* equipmentItemData = Cast<UEquipmentItemData>(itemData);
			if (IsValid(equipmentItemData))
			{
				//Check Valid.
				switch (EquipmentSlot)
				{
				case EEquipmentSlot::Weapon :
					bEquipable = equipmentItemData->EquipmentType == EEquipmentType::Weapon;
					break;
				case EEquipmentSlot::Shield:
					bEquipable = equipmentItemData->EquipmentType == EEquipmentType::Shield;
					break;
				case EEquipmentSlot::Armor:
					bEquipable = equipmentItemData->EquipmentType == EEquipmentType::Armor;
					break;
				case EEquipmentSlot::Accessory1:
				case EEquipmentSlot::Accessory2:
					bEquipable = equipmentItemData->EquipmentType == EEquipmentType::Accessory;
					break;
				default:
					break;
				}

				if (bEquipable)
				{
					switch (EquipmentSlot)
					{
					case EEquipmentSlot::Weapon:
						WeaponData = equipmentItemData;
						break;
					case EEquipmentSlot::Shield:
						ShieldData = equipmentItemData;
						break;
					case EEquipmentSlot::Armor:
						ArmorData = equipmentItemData;
						break;
					case EEquipmentSlot::Accessory1:
						AccessoryData1 = equipmentItemData;
						break;
					case EEquipmentSlot::Accessory2:
						AccessoryData2 = equipmentItemData;
						break;
					default:
						break;
					}

					ApplyEquipment();
				}
			}
		}
	}

	return bEquipable;
}

bool UEquipmentComponent::SetEquipment(EEquipmentSlot EquipmentSlot, UEquipmentItemData* InData)
{
	bool bEquipable = false;

	if (IsValid(InData))
	{
		//Check Valid.
		switch (EquipmentSlot)
		{
		case EEquipmentSlot::Weapon:
			bEquipable = InData->EquipmentType == EEquipmentType::Weapon;
			break;
		case EEquipmentSlot::Shield:
			bEquipable = InData->EquipmentType == EEquipmentType::Shield;
			break;
		case EEquipmentSlot::Armor:
			bEquipable = InData->EquipmentType == EEquipmentType::Armor;
			break;
		case EEquipmentSlot::Accessory1:
		case EEquipmentSlot::Accessory2:
			bEquipable = InData->EquipmentType == EEquipmentType::Accessory;
			break;
		default:
			break;
		}

		if (bEquipable)
		{
			switch (EquipmentSlot)
			{
			case EEquipmentSlot::Weapon:
				WeaponData = InData;
				break;
			case EEquipmentSlot::Shield:
				ShieldData = InData;
				break;
			case EEquipmentSlot::Armor:
				ArmorData = InData;
				break;
			case EEquipmentSlot::Accessory1:
				AccessoryData1 = InData;
				break;
			case EEquipmentSlot::Accessory2:
				AccessoryData2 = InData;
				break;
			default:
				break;
			}

			ApplyEquipment();
		}
	}

	return false;
}

UEquipmentItemData* UEquipmentComponent::GetEquipmentData(EEquipmentSlot Equipmentslot)
{
	switch (Equipmentslot)
	{
	case EEquipmentSlot::Weapon:
		return WeaponData;
	case EEquipmentSlot::Shield:
		return ShieldData;
	case EEquipmentSlot::Armor:
		return ArmorData;
	case EEquipmentSlot::Accessory1:
		return AccessoryData1;
	case EEquipmentSlot::Accessory2:
		return AccessoryData2;
	default:
		return nullptr;
	}
}


//bool UEquipmentComponent::SetEquipWithIndex(int32 Index, FItemDataSlot InData)
//{
//
//	bool bEquipable = false;
//
//	switch (Index)
//	{
//	case 0:
//		bEquipable = EEquipmentType::Weapon == InData.EquipmentType || InData.ItemType == EItemType::None;
//		break;
//	case 1:
//		bEquipable = EEquipmentType::Shield == InData.EquipmentType || InData.ItemType == EItemType::None;
//		break;
//	case 2:
//		bEquipable = EEquipmentType::Armor == InData.EquipmentType || InData.ItemType == EItemType::None;
//		break;
//	case 3:
//	case 4:
//		bEquipable = EEquipmentType::Accessory == InData.EquipmentType || InData.ItemType == EItemType::None;
//		break;
//	default:
//		break;
//	}
//
//	if (bEquipable)
//	{
//		switch (Index)
//		{
//		case 0:
//			WeaponData = InData;
//			break;
//		case 1:
//			ShieldData = InData;
//			break;
//		case 2:
//			ArmorData = InData;
//			break;
//		case 3:
//			AccessoryData1 = InData;
//			break;
//		case 4:
//			AccessoryData2 = InData;
//			break;
//		default:
//			break;
//		}
//
//		//Apply Equipment to Stat when Update Equipment Data.
//		ApplyEquipment();
//	}
//	
//
//	return bEquipable;
//}

//FItemDatalost UEquipmentComponent::GetEquipWithIndex(int32 Index)
//{
//
//	switch (Index)
//	{
//	case 0:
//		return WeaponData;
//
//	case 1:
//		return ShieldData;
//
//	case 2:
//		return ArmorData;
//
//	case 3:
//		return AccessoryData1;
//
//	case 4:
//		return AccessoryData2;
//
//	default:
//		return FItemDataStruct();
//
//	}
//}

bool UEquipmentComponent::SwapWithInventory(EEquipmentSlot Equipmentslot, UInventoryComponent* Inventory, int32 InventoryIndex)
{
	//Swap Equip <-> Inventory.


	if (IsValid(Inventory))
	{
		FItemDataSlot inInventory = Inventory->InventoryArray[InventoryIndex];
		if (IsValid(inInventory.ItemData))
		{
			UItemData* itemData = inInventory.ItemData.GetDefaultObject();

			if (IsValid(itemData))
			{

				//Failed if inventory item is not Equipment.
				UEquipmentItemData* equipmentItemData = Cast<UEquipmentItemData>(itemData);
				UEquipmentItemData* temp = GetEquipmentData(Equipmentslot);
				if (IsValid(equipmentItemData) && IsValid(temp))
				{
					bool bSucceed = SetEquipment(Equipmentslot, inInventory);
					return bSucceed;
				}
			}
		}
	}
	return false;
}

void UEquipmentComponent::ApplyEquipment()
{

	//Remove past Weapon.
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}

	//update Stat along with current Equipments.
	UStatComponent* statComp = GetOwner()->FindComponentByClass<UStatComponent>();
	if (statComp)
	{
		statComp->ClearAdditionalStat();
		statComp->ApplyAdditionalStat(WeaponData);
		statComp->ApplyAdditionalStat(ShieldData);
		statComp->ApplyAdditionalStat(ArmorData);
		statComp->ApplyAdditionalStat(AccessoryData1);
		statComp->ApplyAdditionalStat(AccessoryData2);
	}

	//add New Weapon.
	if (IsValid(WeaponData->WeaponClass))
	{
		ABasicCharacter* OwnerCharacter = Cast<ABasicCharacter>(GetOwner());
		if (OwnerCharacter)
		{
			FActorSpawnParameters params;
			params.Owner = GetOwner();
			CurrentWeapon = GetWorld()->SpawnActor<ABasicWeapon>(WeaponData->WeaponClass,FTransform::Identity, params);
			CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Weapon Equip OK"));
			}
		}
	}
}

