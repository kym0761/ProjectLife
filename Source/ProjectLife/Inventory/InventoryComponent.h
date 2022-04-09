// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryDataChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
		int32 Money;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", Meta = (AllowPrivateAccess = "true"))
		TArray<FItemSlotData> Items;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CheckInventoryHasSpace();
	bool SpendMoney(int32 Spend);
	void GainMoney(int32 Gain);
	bool CheckEnoughMoney(int32 ToCompare);
	void TryMakeInventorySpace(int32 Num);
	bool SwapItemBetweenInventory(UInventoryComponent* From, int32 FromSlot, UInventoryComponent* To, int32 ToSlot);
	FItemSlotData GetInventoryItem(int32 SlotNumber);
	bool SetInventoryItem(int32 SlotNumber, FItemSlotData InData);
	int32 AddItemToInventory(FItemSlotData InData);
	bool CheckPlayerInventoryHasSpace();
	bool UseItemInInventory(int32 ItemIndex);
	bool CheckItemInInventory(FString ItemName, int32 Quantity);
	bool UseItemsInInventory(FString ItemName, int32 Quantity);

	//call when Inventory's Item Data Changed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category ="Inventory")
	FOnInventoryDataChanged OnInventoryDataChanged;

	int32 GetMoney() const;
	void SetMoney(int32 InVal);

	TArray<FItemSlotData> GetItems() const;
	void SetItems(TArray<FItemSlotData> InVal);
};
