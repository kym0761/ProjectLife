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

bool UEquipmentComponent::SetEquipWithIndex(int32 Index, FItemDataStruct InData)
{

	bool bEquipable = false;

	switch (Index)
	{
	case 0:
		bEquipable = EEquipmentType::Weapon == InData.EquipmentType || InData.ItemType == EItemType::None;
		break;
	case 1:
		bEquipable = EEquipmentType::Shield == InData.EquipmentType || InData.ItemType == EItemType::None;
		break;
	case 2:
		bEquipable = EEquipmentType::Armor == InData.EquipmentType || InData.ItemType == EItemType::None;
		break;
	case 3:
	case 4:
		bEquipable = EEquipmentType::Accessory == InData.EquipmentType || InData.ItemType == EItemType::None;
		break;
	default:
		break;
	}

	if (bEquipable)
	{
		switch (Index)
		{
		case 0:
			WeaponData = InData;
			break;
		case 1:
			ShieldData = InData;
			break;
		case 2:
			ArmorData = InData;
			break;
		case 3:
			AccessoryData1 = InData;
			break;
		case 4:
			AccessoryData2 = InData;
			break;
		default:
			break;
		}

		//Apply Equipment to Stat when Update Equipment Data.
		ApplyEquipment();
	}
	

	return bEquipable;
}

FItemDataStruct UEquipmentComponent::GetEquipWithIndex(int32 Index)
{

	switch (Index)
	{
	case 0:
		return WeaponData;

	case 1:
		return ShieldData;

	case 2:
		return ArmorData;

	case 3:
		return AccessoryData1;

	case 4:
		return AccessoryData2;

	default:
		return FItemDataStruct();

	}
}

bool UEquipmentComponent::SwapWithInventory(int32 EquipmentIndex, UInventoryComponent* Inventory, int32 InventoryIndex)
{

	if (Inventory)
	{
		FItemDataStruct inInventory = Inventory->InventoryArray[InventoryIndex];
		FItemDataStruct temp;
		temp = GetEquipWithIndex(EquipmentIndex);
		bool bSucceed = SetEquipWithIndex(EquipmentIndex, inInventory);
		if (bSucceed)
		{
			Inventory->InventoryArray[InventoryIndex] = temp;

			return true;
		}
	}
	
	return false;
}

void UEquipmentComponent::ApplyEquipment()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Destroy();
	}


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
				GEngine->AddOnScreenDebugMessage(FMath::Rand(), 5.0f, FColor::Red, TEXT("Weapon Equip OK?"));
			}

		}
	}


}

