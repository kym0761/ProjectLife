// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"
#include "Base/StatComponent.h"
#include "Base/BasicWeapon.h"
#include "Base/BasicCharacter.h"
#include "GamePlay/ProjectLIfeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory/InventoryComponent.h"

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

bool UEquipmentComponent::SetEquipment(EEquipmentSlot EquipmentSlot, FItemSlotData InData)
{
	bool bEquipable = false;

	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (IsValid(gameInstance))
	{
		FItemData itemData = gameInstance->GetItemDataFromTable(InData.ItemName);

		if (itemData.ItemType == EItemType::Equipment)
		{
			FEquipmentItemData equipmentItemData;

			equipmentItemData = gameInstance->GetEquipmentItemDataFromTable(itemData.Name);

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
		else if (itemData == FItemData())
		{
			switch (EquipmentSlot)
			{
			case EEquipmentSlot::Weapon:
				WeaponData = FEquipmentItemData();
				break;
			case EEquipmentSlot::Shield:
				ShieldData = FEquipmentItemData();
				break;
			case EEquipmentSlot::Armor:
				ArmorData = FEquipmentItemData();
				break;
			case EEquipmentSlot::Accessory1:
				AccessoryData1 = FEquipmentItemData();
				break;
			case EEquipmentSlot::Accessory2:
				AccessoryData2 = FEquipmentItemData();
				break;
			default:
				break;
			}

			bEquipable = true;

			ApplyEquipment();
		}
	}
	else
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(FMath::Rand(), 2.0f, FColor::Blue, TEXT("Cannot Open Data Table..?"));
		}
		return false;
	}

	return bEquipable;
}

bool UEquipmentComponent::SetEquipment(EEquipmentSlot EquipmentSlot, FEquipmentItemData InData)
{
	bool bEquipable = false;

	if (InData.IsEmpty())
	{
		switch (EquipmentSlot)
		{
		case EEquipmentSlot::Weapon:
			WeaponData = FEquipmentItemData();
			bEquipable = true;
			break;
		case EEquipmentSlot::Shield:
			ShieldData = FEquipmentItemData();
			bEquipable = true;
			break;
		case EEquipmentSlot::Armor:
			ArmorData = FEquipmentItemData();
			bEquipable = true;
			break;
		case EEquipmentSlot::Accessory1:
			AccessoryData1 = FEquipmentItemData();
			bEquipable = true;
			break;
		case EEquipmentSlot::Accessory2:
			AccessoryData2 = FEquipmentItemData();
			bEquipable = true;
			break;
		default:
			break;
		}

		ApplyEquipment();
	}
	else
	{
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

bool UEquipmentComponent::SwapWithInventory(EEquipmentSlot Equipmentslot, UInventoryComponent* InventoryComponent, int32 SlotNumber)
{

	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("InventoryComponent is Null."));
		return false;
	}

	FEquipmentItemData currentEquipment = GetEquipmentData(Equipmentslot);
	FItemSlotData fromEquipmentToInventory;

	//장비 데이터를 FItemDataSlot으로 변환.
	UProjectLIfeGameInstance* gameInstance = Cast<UProjectLIfeGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!IsValid(gameInstance))
	{
		UE_LOG(LogTemp, Warning, TEXT("gameInstance is Null."));
		return false;
	}

	FItemData itemData = gameInstance->GetItemDataFromTable(currentEquipment.Name);
	if (fromEquipmentToInventory.ItemName == itemData.Name && fromEquipmentToInventory.ItemName == FString(""))
	{
		//Invalid
		fromEquipmentToInventory.Quantity = 0;
	}
	else
	{
		//Valid
		fromEquipmentToInventory.Quantity = 1;
		fromEquipmentToInventory.ItemName = itemData.Name;
	}


	//장비와 바꿀 인벤토리 아이템의 데이터.
	FItemSlotData inInventory = InventoryComponent->GetInventoryItem(SlotNumber);
	FItemData itemData_InInventory = gameInstance->GetItemDataFromTable(inInventory.ItemName);
	
	//인벤토리 데이터가 장비라면 장비를 교체함.
	if (itemData_InInventory.ItemType == EItemType::Equipment || (itemData_InInventory == FItemData()))
	{
		bool bSucceed = SetEquipment(Equipmentslot, inInventory);
		if (bSucceed)
		{
			InventoryComponent->SetInventoryItem(SlotNumber, fromEquipmentToInventory);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("?"));
		}

		return true;
	}
	else
	{
		if (inInventory.IsEmpty()) // 빈 인벤토리 슬롯인지 확인
		{
			InventoryComponent->SetInventoryItem(SlotNumber, fromEquipmentToInventory);
			SetEquipment(Equipmentslot, FItemSlotData());

			return true;
		}
		else
		{
			//비어있지 않았다면 스왑하지 않기.
			UE_LOG(LogTemp, Warning, TEXT("NO Swap"));
		}
	}

	return false;
}

void UEquipmentComponent::ApplyEquipment()
{
	//TODO : Only Do it When Weapon is Changed?

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
			
			UE_LOG(LogTemp, Warning, TEXT("Weapon Equip OK"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon Equip failed because WeaponClass is Null."));
		}
	}
}

