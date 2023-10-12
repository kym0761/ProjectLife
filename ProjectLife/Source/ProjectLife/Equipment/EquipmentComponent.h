// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class UInventoryComponent;
class ABasicWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEquipmentComponent();

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		FEquipmentItemData WeaponData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		FEquipmentItemData ShieldData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		FEquipmentItemData ArmorData;
	
	/* 2 Slot for Accessories*/
	/*Accessory1*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		FEquipmentItemData AccessoryData1;
	/*Accessory2*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		FEquipmentItemData AccessoryData2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipment", Meta = (AllowPrivateAccess = "true"))
		TObjectPtr<ABasicWeapon> CurrentWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SetEquipment(EEquipmentSlot EquipmentSlot, FItemSlotData InData);
	bool SetEquipment(EEquipmentSlot EquipmentSlot, FEquipmentItemData InData);

	FEquipmentItemData GetEquipmentData(EEquipmentSlot Equipmentslot);
	bool SwapWithInventory(EEquipmentSlot Equipmentslot, UInventoryComponent* InventoryComponent, int32 SlotNumber);

	void ApplyEquipment();
};
