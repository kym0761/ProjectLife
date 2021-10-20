// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "InventoryComponent.h"
#include "../Base/StatComponent.h"
#include "../Base/BasicWeapon.h"
#include "../Base/BasicCharacter.h"
#include "../ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

	FItemData itemData = InData.ItemData;

	if (itemData.ItemType == EItemType::Equipment)
	{
		FEquipmentItemData equipmentItemData;

		UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		if (IsValid(gameInstance))
		{
			equipmentItemData = gameInstance->GetEquipmentItemDataFromTable(itemData.Name);
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Cannot Open Data Table..?"));
			}
			return false;
		}

		//Check Valid.
		switch (EquipmentSlot)
		{
		case EEquipmentSlot::Weapon:
			bEquipable = (equipmentItemData.EquipmentType == EEquipmentType::Weapon);
			break;
		case EEquipmentSlot::Shield:
			bEquipable = (equipmentItemData.EquipmentType == EEquipmentType::Shield);
			break;
		case EEquipmentSlot::Armor:
			bEquipable = (equipmentItemData.EquipmentType == EEquipmentType::Armor);
			break;
		case EEquipmentSlot::Accessory1:
		case EEquipmentSlot::Accessory2:
			bEquipable = (equipmentItemData.EquipmentType == EEquipmentType::Accessory);
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

	return bEquipable;
}

bool UEquipmentComponent::SetEquipment(EEquipmentSlot EquipmentSlot, FEquipmentItemData InData)
{
	bool bEquipable = false;

	//Check Valid.
	switch (EquipmentSlot)
	{
	case EEquipmentSlot::Weapon:
		bEquipable = (InData.EquipmentType == EEquipmentType::Weapon);
		break;
	case EEquipmentSlot::Shield:
		bEquipable = (InData.EquipmentType == EEquipmentType::Shield);
		break;
	case EEquipmentSlot::Armor:
		bEquipable = (InData.EquipmentType == EEquipmentType::Armor);
		break;
	case EEquipmentSlot::Accessory1:
	case EEquipmentSlot::Accessory2:
		bEquipable = (InData.EquipmentType == EEquipmentType::Accessory);
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

	return bEquipable;
}


FEquipmentItemData UEquipmentComponent::GetEquipmentData(EEquipmentSlot Equipmentslot)
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
	default: // maybe not needed.
		return FEquipmentItemData();
	}
}

bool UEquipmentComponent::SwapWithInventory(EEquipmentSlot Equipmentslot, UInventoryComponent* Inventory, int32 InventoryIndex)
{
	//Swap Equip <-> Inventory.


	if (IsValid(Inventory))
	{

		FItemDataSlot inInventory = Inventory->InventoryArray[InventoryIndex];

		if (inInventory.ItemData.ItemType == EItemType::Equipment)
		{
			bool bSucceed = SetEquipment(Equipmentslot, inInventory);
			return bSucceed;
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
	if (IsValid(WeaponData.WeaponClass))
	{
		ABasicCharacter* OwnerCharacter = Cast<ABasicCharacter>(GetOwner());
		if (OwnerCharacter)
		{
			FActorSpawnParameters params;
			params.Owner = GetOwner();
			CurrentWeapon = GetWorld()->SpawnActor<ABasicWeapon>(WeaponData.WeaponClass,FTransform::Identity, params);
			CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Weapon Equip OK"));
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Weapon Equip failed because WeaponClass is Null."));
			}
		}
	}
}

