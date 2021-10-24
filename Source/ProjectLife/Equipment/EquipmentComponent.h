// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		FEquipmentItemData WeaponData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		FEquipmentItemData ShieldData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		FEquipmentItemData ArmorData;

	/* 2 Slot for Accessories*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		FEquipmentItemData AccessoryData1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment")
		FEquipmentItemData AccessoryData2;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Equipment")
		ABasicWeapon* CurrentWeapon;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool SetEquipment(EEquipmentSlot EquipmentSlot, FItemDataSlot InData);
	bool SetEquipment(EEquipmentSlot EquipmentSlot, FEquipmentItemData InData);

	FEquipmentItemData GetEquipmentData(EEquipmentSlot Equipmentslot);
	bool SwapWithInventory(EEquipmentSlot Equipmentslot, UInventoryComponent* Inventory, int32 InventoryIndex);

	void ApplyEquipment();
};
