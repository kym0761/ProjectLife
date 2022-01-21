// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Item/ItemStruct.h"
#include "InventoryManager.generated.h"

class AItemPickup;

UCLASS()
class UInventory : public UObject
{
	GENERATED_BODY()

public:

	UInventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemDataSlot> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxCapacity;

};

UCLASS()
class PROJECTLIFE_API AInventoryManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryManager();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TMap<int32, UInventory*> Inventories;

	const int32 PLAYER_INVENTORY = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool CheckValidInventory(int32 InventoryNumber);

	bool CheckInventoryHasSpace(int32 InventoryNumber);

	int32 GetCurrentMoney();
	bool SpendMoney(int32 OutMoney);
	void GainMoney(int32 InMoney);
	bool CheckEnoughMoney(int32 ToCompare);
	void TryMakeInventorySpace(int32 Num);
	bool SwapItemBetweenInventory(int32 From,int32 FromSlot, int32 To, int32 ToSlot);
	FItemDataSlot GetInventoryItem(int32 InventoryNumber, int32 SlotNumber);
	bool SetInventoryItem(int32 InventoryNumber, int32 SlotNumber, FItemDataSlot InData);
	FItemDataSlot AddItemToInventory(FItemDataSlot InData);

	bool AddPickupToInventory(AItemPickup* Pickup);
	

};
