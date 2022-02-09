// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemStruct.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTLIFE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		int32 Money;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FItemDataSlot> Items;

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
	FItemDataSlot GetInventoryItem(int32 SlotNumber);
	bool SetInventoryItem(int32 SlotNumber, FItemDataSlot InData);
	int32 AddItemToInventory(FItemDataSlot InData);

	bool CheckPlayerInventoryHasSpace();

};
